#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "c8_cpu.h"
#include "c8_op_codes.h"

/************************************************************
*   CHIP8 Memory Map - 4K total (4096 Bytes)                *
*                                                           *
*   0x000 - 0x1FF -> CHIP 8 Interpreter                     *
*   0x050 - 0x0A0 -> Used for built in 4x5 pixel font set   *
*   0x200 - 0xFFF -> Program ROM and working RAM            *
************************************************************/

#define INTERNAL static

#define C8_REG_COUNT 16
#define C8_STACK_SIZE 16
#define C8_HEX_KEYS 16
#define C8_RAM_SIZE 4096
#define C8_SCREEN_PIXELS (64 * 32)

#define C8_INITIAL_ADDRESS 0x200

typedef unsigned char C8_REG_8;
typedef unsigned short C8_REG_16;
typedef unsigned int C8_REG_32; 

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

  C8_BYTE hex_keypad[C8_HEX_KEYS];       // Stores key states

  C8_BYTE ram[C8_RAM_SIZE];

  C8_BYTE screen[C8_SCREEN_PIXELS];
};

INTERNAL void
c8_mem_dump(struct c8_cpu* cpu) {
  //TODO(bryan) set up proper logging, and dump this to file
  C8_BYTE* ram = cpu->ram;
  int i;
  for (i = 1; i <= C8_RAM_SIZE; i++) {
    C8_REG_16 addr = ram[i] << 8 | ram[i + 1];
    fprintf(stdout, "Addr: %d - 0x%d  ", i, addr);
    if (i % 4  == 0) {
      fprintf(stdout, "\n");
    }
  }
}

struct c8_cpu*
c8_cpu_init(void) {
  struct c8_cpu* cpu = calloc(1, sizeof(struct c8_cpu));

  // set program counter
  cpu->reg_pc = C8_INITIAL_ADDRESS;

  //TODO(bryan) load font set
  return cpu;
}

void
c8_cpu_load_rom(struct c8_cpu* cpu, C8_BYTE* rom, int rom_size) {
  memcpy(&cpu->ram[C8_INITIAL_ADDRESS], rom, rom_size);
}

void
c8_cpu_destroy(struct c8_cpu* cpu) {
  if (cpu) {
    free(cpu);
  }
}

INTERNAL C8_REG_16
c8_fetch(struct c8_cpu* cpu) {
  C8_REG_16 pc = cpu->reg_pc;
  C8_BYTE* ram = cpu->ram;
  return ram[pc] << 8 | ram[pc + 1];
}

INTERNAL void
c8_decode(struct c8_cpu* cpu, C8_REG_16 op_code) {
  switch(op_code & AND_TOP_MSK) {
    C8_REG_16 vx;
    C8_REG_16 vy;
    C8_REG_16 imm;
    C8_REG_32 addr;
    case OP_0000:
      switch (op_code & AND_BOT_MSK) {
        case OP_CLR_SCN:
          // clear screen
          break;
        case OP_SUB_RTN:
          // pop stack, adjust pc
          break;
        default:
          //TODO(bryan) log error
          c8_mem_dump(cpu);
          exit(2);
          break;
      }
    case OP_JMP_ADR:
      // decode address, adjust pc
      break;
    case OP_CLL_SUB:
      // push pc on stack, adjust pc
      break;
    case OP_TST_EQ:
      vx = op_code & 0x0F00;
      imm = op_code & 0x00FF;
      if (cpu->reg_v[vx] == imm) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_TST_NEQ:
      vx = op_code & 0x0F00;
      imm = op_code & 0x00FF;
      if (cpu->reg_v[vx] != imm) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_EQ_EQ:
      vx = op_code & 0x0F00;
      vy = op_code & 0x00F0;
      if (cpu->reg_v[vx] == cpu->reg_v[vy]) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_SET_IMM:
      vx = op_code & 0x0F00;
      imm = op_code & 0x0FF;
      cpu->reg_v[vx] = imm;
      cpu->reg_pc += 2;
      break;
    case OP_ADD_IMM:
      vx = op_code & 0x0F00;
      imm = op_code & 0x00FF;
      cpu->reg_v[vx] += imm;
      break;
  }
}

void
c8_cpu_cycle(struct c8_cpu* cpu) {

  C8_REG_16 op_code = c8_fetch(cpu);
  fprintf(stdout, "Fetched OPCode: 0x%d\n", op_code);
  c8_decode(cpu, op_code);

  // update timers
}

short
c8_cpu_draw_flag_set(struct c8_cpu* cpu) {
  (void)cpu;
  return 0; //TODO(bryan) implement
}

void
c8_cpu_update_key_state(struct c8_cpu* cpu) {
  (void)cpu;
  //TODO(bryan) implement
}



