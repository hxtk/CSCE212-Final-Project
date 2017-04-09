
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
