// SDL Graphics Context Implementation
#include <SDL2/SDL.h>
#include "c8_gfx_context.h"

struct c8_gfx_context {
  SDL_Window* window;
  SDL_Renderer* renderer;
};

struct c8_gfx_context*
c8_gfx_init(int width, int height, char* title) {
  struct c8_gfx_context* gfx = malloc(sizeof(struct c8_gfx_context));
  SDL_CreateWindowAndRenderer(width, height, 0, &gfx->window, &gfx->renderer);
  SDL_SetWindowTitle(gfx->window, title);
  return gfx;
}

void
c8_gfx_destroy(struct c8_gfx_context* gfx) {
  if (gfx) {
    SDL_DestroyWindow(gfx->window);
    SDL_DestroyRenderer(gfx->renderer);
    free(gfx);
  }
}

void
c8_gfx_update_keys(struct c8_gfx_context* gfx) {
  //TODO(bryan) better handling here
  (void)gfx;
  SDL_Event event;
  if (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        exit(0);
        break;
      default:
        break;
    }
  }
}

void
c8_gfx_clear(struct c8_gfx_context* gfx) {
  SDL_SetRenderDrawColor(gfx->renderer, 255, 255, 255, 255);
  SDL_RenderClear(gfx->renderer);
}

void
c8_gfx_draw(struct c8_gfx_context* gfx,
    void* buffer,
    size_t element_size,
    int buffer_size) {
  (void)buffer;
  (void)element_size;
  (void)buffer_size;
  //TODO(bryan) render screen
  SDL_RenderPresent(gfx->renderer);
}
