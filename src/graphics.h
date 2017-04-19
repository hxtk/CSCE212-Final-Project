// Copyright: Peter Sanders. All rights reserved.
// Date: 2017-04-06
//
// This header defines the structures and functions for 2d graphics rendering
// on the GameBoy Advance.

#include <stdlib.h>

#include "gba.h"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define G_RECT_COLLISION_X 0x3  // = 0b0011
#define G_RECT_COLLISION_Y 0xC  // = 0b1100

// This is a point. It is the most basic graphics primitive, and is the basis
// for |g_line|, |g_polygon|, etc. It consists only of an X and a Y coordinate
// which should be bounds-checked for the resolution of the video mode, e.g.,
// 0 <= x < 240; 0 <= y < 160.
typedef struct g_point {
  int x;
  int y;
} g_point;

typedef struct g_point_f {
  float x;
  float y;
} g_point_f;

// This describes a rectangle that is aligned with the axes. Due to the absence
// of diagonal edges, this shape can be rendered much more quickly than
// arbitrary polygons.
typedef struct g_aligned_rect {
  g_point start;
  int width;
  int height;
  int color;

} g_aligned_rect;

typedef struct g_aligned_rect_f {
  g_point_f start;
  float width;
  float height;
  int color;
} g_aligned_rect_f;

void g_render_rectangle(const g_aligned_rect rectangle);
void g_render_rectangle_f(const g_aligned_rect_f rectangle);

// This provides the collision matrix between two rectangles. The collision mask
// is four bits such that:
//     0b0001 = 0x1 → |lhs| is right of |rhs|'s left edge
//     0b0010 = 0x2 → |lhs| is left of |rhs|'s right edge
//     0b0100 = 0x4 → |lhs| is below |rhs|'s top edge
//     0b1000 = 0x8 → |lhs| is above |rhs|'s bottom edge
// A collision has occurred if the return value is equal to 0xA
int g_rect_collide_f(const g_aligned_rect_f* lhs, const g_aligned_rect_f* rhs);

#endif  // GRAPHICS_H_
