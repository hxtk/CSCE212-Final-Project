
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
