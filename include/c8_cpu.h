#ifndef C8_CPU_H
#define C8_CPU_H

typedef unsigned char C8_BYTE;

struct c8_cpu;

struct c8_cpu*
c8_cpu_init(void);

void
c8_cpu_destroy(struct c8_cpu*);

void
c8_cpu_cycle(struct c8_cpu*);

short
c8_cpu_draw_flag_set(struct c8_cpu*);

void
c8_cpu_update_key_state(struct c8_cpu*);

#endif
