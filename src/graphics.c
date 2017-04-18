
#include "gba.h"
#include "graphics.h"

void g_render_rectangle(const g_aligned_rect rectangle) {
  for (int i = 0; i < rectangle.height; ++i) {
    for (int j = 0; j < rectangle.width; ++j) {
      gba_set_pixel(j + rectangle.start.x,
		    i + rectangle.start.y,
		    rectangle.color);
    }
  }
}

void g_render_rectangle_f(const g_aligned_rect_f rectangle) {
  g_aligned_rect int_rect;
  int_rect.start.x = (int) (rectangle.start.x + 0.5);
  int_rect.start.y = (int) (rectangle.start.y + 0.5);
  int_rect.width = (int) (rectangle.width + 0.5);
  int_rect.height = (int) (rectangle.height + 0.5);
  int_rect.color = rectangle.color;

  g_render_rectangle(int_rect);
}

int g_rect_collide_f(const g_aligned_rect_f* lhs, const g_aligned_rect_f* rhs) {
  int response = 0;

  // 0b0001 = 0x1 → |lhs| is right of |rhs|'s left edge
  if (lhs->start.x < rhs->start.x + rhs->width) {
    response |= 0x1;
  }
  // 0b0010 = 0x2 → |lhs| is left of |rhs|'s right edge
  if (lhs->start.x + lhs->width > rhs->start.x) {
    response |= 0x2;
  }
  // 0b0100 = 0x4 → |lhs| is below |rhs|'s top edge
  if (lhs->start.y < rhs->start.y + rhs->height) {
    response |= 0x4;
  }
  // 0b1000 = 0x8 → |lhs| is above |rhs|'s bottom edge
  if (lhs->start.y + lhs->height > rhs->start.y) {
    response |= 0x8;
  }
  return response;
}
