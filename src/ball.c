// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-09

#include "ball.h"

#include <stdlib.h>
#include <time.h>

#include "graphics.h"
#include "gba.h"

#include "player.h"

#define SPEED 1.5

static g_aligned_rect_f ball;
static g_aligned_rect_f ball_range;

static g_point_f velocity;

static void ball_reinit() {
  static first_run = true;
  static seeded = false;

  // The first call will be from the |init()| function. We do not determine the
  // seed at first run because time will be predictable at first run.
  if (!first_run && !seeded) {
    srand(time(NULL));
    seeded = true;
  }

  // Set the velocity to some arbitrary vector with a magnitude of |1|
  // which has a horizontal component of at least |1|
  if (seeded) {
    // 0.5 + a random number on the range (0, 0.5)
    velocity.x = 0.5 + ((float)(rand()) / 2.0 / (float)(RAND_MAX));

    // sin(x) = 1 - cos²(x)
    velocity.y = 1.0 - (velocity.x * velocity.x);

    // The above algorithm can only produce velocity vectors in the first
    // quadrent. This enables the other three 
    if (rand() & 2) {
      velocity.x = -velocity.x;
    }
    if (rand() & 2) {
      velocity.y = -velocity.y;
    }

    velocity.x *= SPEED;
    velocity.y *= SPEED;
  } else {
    velocity.x = 1;
    velocity.y = 1;
  }

  // Place the ball in the middle of the screen
  ball.start.x = GBA_MAX_X / 2;
  ball.start.y = GBA_MAX_Y / 2;
  ball.width = 5;
  ball.height = 5;

  // Range must extend two pixels in all directions
  // because the velocity of the ball has a magnitude of sqrt(2)
  ball_range.start.x = ball.start.x - 2;
  ball_range.start.y = ball.start.y - 2;
  ball_range.width = ball.width + 4;
  ball_range.height = ball.height + 4;

  first_run = false;
}

void ball_init(int color, int background) {
  ball.color = color;
  ball_range.color = background;
  ball_reinit();
}

void ball_clear() {
  g_render_rectangle_f(ball_range);
}

void ball_update() {
  static int player_mask = 0;
  
  ball.start.x += velocity.x;
  ball.start.y += velocity.y;

  ball_range.start.x += velocity.x;
  ball_range.start.y += velocity.y;

  // Get the new collision bitmask between the player and the ball
  int new_player_mask = g_rect_collide_f(&ball, player_struct());

  // If the ball is in a collision state then determine the axis of the
  // collision and bounce the ball accordingly.
  if (new_player_mask == 0xf) {
    int difference_mask = player_mask ^ new_player_mask;
    if (difference_mask & G_RECT_COLLISION_X) {
      velocity.x = -velocity.x;
    }
    if (difference_mask & G_RECT_COLLISION_Y) {
      velocity.y = -velocity.y;
    }
  }
  // Update the old bitmask
  player_mask = new_player_mask;

  // Reset if it passes left wall
  if (ball.start.x + ball.width + 2 <= 0) {
    ball_reinit();
  }

  // Collide with right wall
  if (ball.start.x + 3 >= GBA_MAX_X) {
    velocity.x = -velocity.x;
  }

  // Collide with the top and bottom walls
  if (ball.start.y + 2 <= 0 || ball.start.y + 3 >= GBA_MAX_Y)
    velocity.y = -velocity.y;

  if (!(*gba_buttons & GBA_BUTTON_START)) {
    ball_clear();
    ball_reinit();
  }
}

void ball_render() {
  g_render_rectangle_f(ball);
}
