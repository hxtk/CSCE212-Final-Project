// Copyright: Peter Sanders
// Date: 2017-04-09

#include "graphics.h"
#include "gba.h"

#ifndef PLAYER_H_
#define PLAYER_H_

// Accepts the color of the player and the color of the background
// This initializes the variables for the area to be cleared as well as
// the player object itself. It must be called before any of the other members.
void player_init(int color, int background);

// Clear the area where the player was last frame. For greater efficiency, this
// could check if the player position has changed and only clear those values.
// As of 2017-04-11, this is not necessary. As long as the main loop is shorter
// than ~15ms, we do not gain increased performance from increased efficiency.
void player_clear();

void player_render();

// Poll the keyboard for input. "Up" and "Down" move the player up and down.
// No other input events are being handled.
void player_input();

// Returns a pointer to the player structure
g_aligned_rect_f* player_struct();

#endif  // PLAYER_H_
