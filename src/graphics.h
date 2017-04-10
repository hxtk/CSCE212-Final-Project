// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-06
//
// This header defines the structures and functions for 2d graphics rendering
// on the GameBoy Advance.

#include <stdlib.h>

#include "gba.h"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

// This is a point. It is the most basic graphics primitive, and is the basis
// for |g_line|, |g_polygon|, etc. It consists only of an X and a Y coordinate
// which should be bounds-checked for the resolution of the video mode, e.g.,
// 0 <= x < 240; 0 <= y < 160.
typedef struct g_point {
  int x;
  int y;
} g_point;

// This describes a rectangle that is aligned with the axes. Due to the absence
// of diagonal edges, this shape can be rendered much more quickly than
// arbitrary polygons.
typedef struct g_aligned_rect {
  g_point start;
  int width;
  int height;
  int color;

} g_aligned_rect;

void g_render_rectangle(const g_aligned_rect rectangle);

#endif  // GRAPHICS_H_
