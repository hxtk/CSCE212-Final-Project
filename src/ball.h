

#include "graphics.h"
#include "gba.h"

#ifndef BALL_H_
#define BALL_H_

static g_aligned_rect ball;
static g_aligned_rect ball_range;

extern g_point velocity;

void init_ball(int color, int background);

void clear_ball();

void update_ball();

void render_ball();

#endif  // BALL_H_
