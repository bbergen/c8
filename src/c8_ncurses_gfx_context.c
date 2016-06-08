#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
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

  initscr();
  noecho();
  curs_set(0);

  int x = 0;
  int y = 0;

  while (1) {
    clear();
    mvprintw(y, x, "x");
    refresh();
    usleep(300000);
    x++;
  }

  sleep(1);
  endwin();
  return malloc(sizeof(struct c8_gfx_context));
}

void 
c8_gfx_destroy(struct c8_gfx_context* gfx) {
  if (gfx) {
    free(gfx);
  }
}

