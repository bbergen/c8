#include "c8_cpu.h"

/************************************************************
*   CHIP8 Memory Map - 4K total (4096 Bytes)                *
*                                                           *
*   0x000 - 0x1FF -> CHIP 8 Interpreter                     *
*   0x050 - 0x0A0 -> Used for built in 4x5 pixel font set   *
*   0x200 - 0xFFF -> Program ROM and working RAM            *
************************************************************/

#define C8_REG_COUNT 16
#define C8_STACK_SIZE 16
#define C8_HEX_KEYS 16

typedef unsigned char C8_REG_8;
typedef unsigned short C8_REG_16;

struct c8_stack {
  C8_BYTE c8_stack[C8_STACK_SIZE];
  C8_BYTE stack_pointer;
};

struct c8_cpu {
  C8_REG_8 reg_v[C8_REG_COUNT];             // General Purpose Regs
  C8_REG_16 reg_opcode;                     // Current Opcode Reg
  C8_REG_16 reg_index;                      // Index Reg
  C8_REG_16 reg_pc;                         // Program Counter

  C8_REG_8 reg_delay_timer;                 // When non zero, counts down
  C8_REG_8 reg_sound_timer;                 // Plays sound when zero

  struct c8_stack stack;                    // Stores function return

  C8_BYTE c8_hex_keypad[C8_HEX_KEYS];       // Stores key states
};
