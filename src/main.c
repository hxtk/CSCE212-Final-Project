// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-08

#include "player.h"
#include "gba.h"

int main() {
  // Set video mode to double-buffered with BG2 enabled
  *gba_display_control = GBA_VIDEO_MODE4 | GBA_VIDEO_BG2;

  // Define color palette
  int black = gba_add_color(0x0000);
  int white = gba_add_color(0x7fff);
  int red = gba_add_color(0x001f);
  int blue = gba_add_color(0x7c00);

  // Initialize objects
  player_init(blue, black);

  // Initialize screen
  gba_fill_buffer(black);
  gba_refresh();
  gba_fill_buffer(black);

  // Main game loop; runs infinitely.
  float y = GBA_MAX_Y / 2 - 16;
  while(1) {
    // Clear old frame
    player_clear();

    // Update objects
    player_input();

    // Render new frame
    player_render();    

    // Display rendered frame
    gba_sync();
    gba_refresh();
  }

  return 0;
}
