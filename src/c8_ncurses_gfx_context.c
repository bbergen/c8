#include <stdlib.h>
#include "c8_gfx_context.h"

struct c8_gfx_context {
  //TODO(bryan) implement
};

void
c8_gfx_draw(struct c8_gfx_context* gfx) {
  (void)gfx;
}

void
c8_gfx_clear(struct c8_gfx_context* gfx) {
  (void)gfx;
}

void
c8_gfx_update_keys(struct c8_gfx_context* gfx) {
  (void)gfx;
}

struct c8_gfx_context*
c8_gfx_init(int width, int height, char* title) {
  (void)width;
  (void)height;
  (void)title;
  return malloc(sizeof(struct c8_gfx_context));
}

void 
c8_gfx_destroy(struct c8_gfx_context* gfx) {
  if (gfx) {
    free(gfx);
  }
}

