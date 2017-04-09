// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-08

#include "graphics.h"
#include "gba.h"

void input(g_point* point) {
  if (!(*gba_buttons & GBA_BUTTON_UP) && (point->y + 16 > 0))
    point->y -= 1;

  if (!(*gba_buttons & GBA_BUTTON_DOWN) && (point->y + 16 < GBA_MAX_Y))
    point->y += 1;
}

int main() {
  // Set video mode to double-buffered with BG2 enabled
  *gba_display_control = GBA_VIDEO_MODE4 | GBA_VIDEO_BG2;
  
  int black = gba_add_color(0x0000);
  int white = gba_add_color(0x7fff);
  int red = gba_add_color(0x001f);
  int blue = gba_add_color(0x7c00);

  g_aligned_rect player_range;
  player_range.start.x = 15;
  player_range.start.y = 0;
  player_range.width = 5;
  player_range.height = GBA_MAX_Y;
  player_range.color = black;

  g_aligned_rect player;
  player.start.x = 15;
  player.start.y = GBA_MAX_Y / 2 - 16;
  player.width = 5;
  player.height = 32;
  player.color = blue;

  gba_fill_buffer(black);
  gba_refresh();
  gba_fill_buffer(black);

  // Main game loop; runs infinitely.
  float y = GBA_MAX_Y / 2 - 16;
  while(1) {
    // Clear old render
    g_render_rectangle(player_range);

    input(&player.start);

    g_render_rectangle(player);

    gba_sync();
    gba_refresh();
  }

  return 0;
}
