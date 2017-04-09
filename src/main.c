// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-08

#include "gba.h"

void draw_rect(int x, int y, int width, int height, int color) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      gba_set_pixel((x + j), (y + i), color);
    }
  }
}

void input(float* y) {
  if (!(*gba_buttons & GBA_BUTTON_UP) && (*y + 16 > 0))
    *y -= 1;

  if (!(*gba_buttons & GBA_BUTTON_DOWN) && (*y + 16 < GBA_MAX_Y))
    *y += 1;
}

int main() {
  // Set video mode to double-buffered with BG2 enabled
  *gba_display_control = GBA_VIDEO_MODE4 | GBA_VIDEO_BG2;
  
  int black = gba_add_color(0x0000);
  int white = gba_add_color(0x7fff);
  int red = gba_add_color(0x001f);
  int blue = gba_add_color(0x7c00);

  gba_fill_buffer(black);
  gba_refresh();
  gba_fill_buffer(black);

  // Main game loop; runs infinitely.
  float y = GBA_MAX_Y / 2 - 16;
  while(1) {
    // Clear old render
    draw_rect(15, 0, 5, GBA_MAX_Y, black);

    input(&y);

    draw_rect(15, y, 5, 32, blue);

    gba_sync();
    gba_refresh();
  }

  return 0;
}
