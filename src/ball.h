// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-09

#include "graphics.h"
#include "gba.h"

#ifndef BALL_H_
#define BALL_H_

extern g_point velocity;

// Initialize |ball| and |ball_range| to the center of the screen, with
// |ball_range| surrounding |ball| evenly on all sides by a margin of the maximum
// magnitude of |velocity|
void ball_init(int color, int background);

// Fill the area around the ball (i.e., the ball plus the maximum distance it
// could travel in a single frame) with the background color in order to clear it
void ball_clear();

// Add the velocity vector to the position vector of both the |ball| and
// |ball_range| in order to clear the ball properly between renders.
// Presently, collisions are also checked here and the velocity vector is changed
// as needed to reflect an elastic collision. This may change in future versions
// when collisions need to include other objects instead of just the arena walls.
void ball_update();

void ball_render();

#endif  // BALL_H_
