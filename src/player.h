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

// Clear the area in which the player may exist. This should be called before
// any call is made to |player_render()|.
//
// TODO: define a render area that consists only of the amount the player
// could have moved since the last frame.
void player_clear();

void player_render();

// Poll the keyboard for input. "Up" and "Down" move the player up and down.
// No other input events are being handled.
void player_input();

#endif  // PLAYER_H_
