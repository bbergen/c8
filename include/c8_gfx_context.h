#ifndef C8_GFX_CONTEXT_H
#define C8_GFX_CONTEXT_H

struct c8_gfx_context;

void
c8_gfx_draw(struct c8_gfx_context*);

void
c8_gfx_clear(struct c8_gfx_context*);

struct c8_gfx_context*
c8_gfx_init(void);

void
c8_gfx_destroy(struct c8_gfx_context*);

#endif
