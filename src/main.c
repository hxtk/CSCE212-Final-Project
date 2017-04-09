// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-08

#include "ball.h"
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
  ball_init(white, black);

  // Initialize screen
  gba_fill_buffer(black);
  gba_refresh();
  gba_fill_buffer(black);

  // Main game loop; runs infinitely.
  while(1) {
    // Clear old frame
    player_clear();
    ball_clear();

    // Update objects
    player_input();
    ball_update();

    // Render new frame
    ball_render();
    player_render();    

    // Display rendered frame
    gba_sync();
    gba_refresh();
  }

  return 0;
}
