

#include "graphics.h"
#include "gba.h"

#ifndef BALL_H_
#define BALL_H_

static g_aligned_rect ball;
static g_aligned_rect ball_range;

extern g_point velocity;

void ball_init(int color, int background);

void ball_clear();

void ball_update();

void ball_render();

#endif  // BALL_H_
