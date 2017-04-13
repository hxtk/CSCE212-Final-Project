// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-09

#include "player.h"

#include "graphics.h"
#include "gba.h"

static g_aligned_rect player_prev;
static g_aligned_rect player;

void player_init(int color, int background) {
  player.start.x = 15;
  player.start.y = GBA_MAX_Y / 2 - 16;
  player.width = 5;
  player.height = 32;
  player.color = color;

  player_prev = player;
  player_prev.color = background;
}

void player_clear() {
  g_render_rectangle(player_prev);
}

void player_input() {
  player_prev.start = player.start;

  if (!(*gba_buttons & GBA_BUTTON_UP) && (player.start.y + 16 > 0))
    player.start.y -= 1;

  if (!(*gba_buttons & GBA_BUTTON_DOWN) && (player.start.y + 16 < GBA_MAX_Y))
    player.start.y += 1;
}

void player_render() {
  g_render_rectangle(player);
}
