

#include "ball.h"

#include "graphics.h"
#include "gba.h"

g_point velocity = {1, 1};

void ball_init(int color, int background) {
  ball.start.x = GBA_MAX_X / 2;
  ball.start.y = GBA_MAX_Y / 2;
  ball.width = 5;
  ball.height = 5;
  ball.color = color;

  // Range must extend two pixels in all directions
  // because the velocity of the ball has a magnitude of sqrt(2)
  ball_range.start.x = ball.start.x - 2;
  ball_range.start.y = ball.start.y - 2;
  ball_range.width = ball.width + 4;
  ball_range.height = ball.height + 4;
  ball_range.color = background;
}

void ball_clear() {
  g_render_rectangle(ball_range);
}

void ball_update() {
  ball.start.x += velocity.x;
  ball.start.y += velocity.y;

  ball_range.start.x += velocity.x;
  ball_range.start.y += velocity.y;

  if (ball.start.x + 2 <= 0 || ball.start.x + 3 >= GBA_MAX_X)
    velocity.x = -velocity.x;

  if (ball.start.y + 2 <= 0 || ball.start.y + 3 >= GBA_MAX_Y)
    velocity.y = -velocity.y;
 
}

void ball_render() {
  g_render_rectangle(ball);
}
