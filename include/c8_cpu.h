#ifndef C8_CPU_H
#define C8_CPU_H

/*
* 8 bits
*/
typedef unsigned char C8_BYTE;

/*
* Representation of the CHIP8 Processor
* and accompanying 'hardware' (RAM, Screen Pixels, etc)
*/
struct c8_cpu;

/*
* Allocates and initializes a c8_cpu for use
*/
struct c8_cpu*
c8_cpu_init(void);

/*
* Maps a loaded rom to the c8_cpu's memory space
*/
void
c8_cpu_load_rom(struct c8_cpu*, C8_BYTE*, int);

/*
* Deallocates all memory associated with the c8_cpu
*/
void
c8_cpu_destroy(struct c8_cpu*);

/*
* Executes one Fetch, Decode, Execute, Timer cycle on the c8_cpu
*/
void
c8_cpu_cycle(struct c8_cpu*);

/*
* Returns non-zero if the screen should be redrawn
*/
short
c8_cpu_draw_flag_set(struct c8_cpu*);

/*
* Updates key presses 
* //TODO(bryan) this will likely change with I/O implementation
*/
void
c8_cpu_update_key_state(struct c8_cpu*);

#endif
