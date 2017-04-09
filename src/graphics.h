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

/*
// This describes a line of width |width| between two points |start| and |end|. 
typedef struct g_line {
  g_point start;
  g_point end;
  int color;
  int width;
} g_line;

// This describes a polygon defined by an array of |g_point|s and a color.
// It is rendered using a ray-casting algorithm which can be very expensive for
// complex shapes. Prefer primitive shapes when possible.
typedef struct g_polygon {
  g_point* points;
  int num_points;
  int color;
} g_polygon;
*/

// This describes a rectangle that is aligned with the axes. Due to the absence
// of diagonal edges, this shape can be rendered much more quickly than
// arbitrary polygons.
typedef struct g_aligned_rect {
  g_point start;
  int width;
  int height;
  int color;

} g_aligned_rect;

/*
// 
static int ray_crosses_edge(const g_point& point,
			    const g_point& v1,
			    const g_point& v2);

// This is a 2d ray casting algorithm. We must determine if a point lies within
// a given polygon. This is roughly equivalent to the graph theory problem of
// testing for existence of an Euler circuit which starts and ends outside the
// shape. We test this by casting a ray from the point to infinity and counting
// the number of edges crossed. If an odd number of edges are crossed, the point
// must lie within the shape.
static int point_within_polygon(const g_point& point, const g_polygon& polygon);


void g_render_polygon(const g_polygon& polygon);*/

void g_render_rectangle(const g_aligned_rect rectangle);

#endif  // GRAPHICS_H_
