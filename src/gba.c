// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-09

#include "gba.h"

volatile uint16_t (*const gba_color_mat_front)[120] = (void*) 0x06000000;
volatile uint16_t (*const gba_color_mat_back)[120] = (void*) 0x0600a000;

volatile uint16_t* const gba_color_palette = (uint16_t*) 0x05000000;
volatile uint16_t* const gba_scan_line = (uint16_t*) 0x04000006;
volatile uint16_t* const gba_buttons = (uint16_t*) 0x04000130;

volatile unsigned long* const gba_display_control = (unsigned long*) 0x04000000;

void gba_sync() {
  while(*gba_scan_line < 160);
}

void gba_refresh() {
  // If this bit is set on the display control, the second buffer will be
  // drawn to the screen. Otherwise the first buffer will be drawn.
  *gba_display_control ^= 0x10;
}

void gba_fill_buffer(int color_id) {
  // If this bit is set then the first buffer is the working buffer (because
  // the second buffer is the display buffer). To prevent screen tearing, we
  // only allow the working buffer to be modified.
  volatile uint16_t (*const buffer)[120] = (*gba_display_control & 0x10) ?
                                           gba_color_mat_front :
                                           gba_color_mat_back;

  // It is only necessary to compute the color block once because it is reused
  // for all pixels and we do not care about battering the neighboring values.
  uint16_t color_block = color_id | ((uint16_t)(color_id) << 8);

  // Set the entire buffer to the color block defined above
  for (int i = 0; i < GBA_MAX_Y; ++i) {
    for (int j = 0; j*2 < GBA_MAX_X; ++j) {
      buffer[i][j] = color_block;
    }
  }
}

int gba_set_pixel(int x, int y, int color_id) {
  if (color_id < 0 || color_id >= 256) return false;
  if (y >= GBA_MAX_Y || y < 0 || x >= GBA_MAX_X || x < 0) return false;

  // If this bit is set then the first buffer is the working buffer (because
  // the second buffer is the display buffer). To prevent screen tearing, we
  // only allow the working buffer to be modified.
  volatile uint16_t (*const buffer)[120] = (*gba_display_control & 0x10) ?
                                           gba_color_mat_front :
                                           gba_color_mat_back;

  // Each 16-bit block is two bytes responsible for different pixels which cannot
  // be altered independently. First we mask out the byte we will be altering
  // by ANDing the pair with 0x00 for the byte to clear and 0xff for the byte
  // that should be unchanged. Since `0x00 | n == n`, we then OR the block with
  // the desired byte, shifted into the proper position as necessary.
  if (x & 1) {
    buffer[y][x/2] &= 0x00ff;
    buffer[y][x/2] |= (uint16_t) (color_id) << 8;
  } else {
    buffer[y][x/2] &= 0xff00;
    buffer[y][x/2] |= (uint16_t) (color_id);
  }

  return true;
}

int gba_add_color(uint16_t color) {
  // This is the index at which the color will be stored. We initialize it to -1
  // so that we can preincrement it to simplify the code, i.e., the first index
  // used will be |gba_color_palette[0]|.
  static int index = -1;

  gba_color_palette[++index] = color;
  return index;
}
