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
#define C8_CARRY 15

#define C8_INITIAL_ADDRESS 0x200

typedef unsigned short C8_INT_16;

struct c8_stack {
  C8_INT_16 data[C8_STACK_SIZE];
  C8_INT_16 pointer;
};

struct c8_cpu {
  C8_BYTE reg_v[C8_REG_COUNT];              // General Purpose Regs
  C8_INT_16 reg_opcode;                     // Current Opcode Reg
  C8_INT_16 reg_index;                      // Index Reg
  C8_INT_16 reg_pc;                         // Program Counter

  C8_BYTE reg_delay_timer;                  // When non zero, counts down
  C8_BYTE reg_sound_timer;                  // Plays sound when zero

  struct c8_stack stack;                    // Stores function return

  C8_BYTE keys[C8_HEX_KEYS];                // Stores key states

  C8_BYTE ram[C8_RAM_SIZE];                 // 4kb System Ram

  C8_BYTE screen[C8_SCREEN_PIXELS];         // 64x32 pixel b&w display
};

INTERNAL void
c8_stack_push(struct c8_stack* stack, C8_INT_16 x) {
  if (stack->pointer >= C8_STACK_SIZE) {
    // stack overflow
    //TODO(bryan) add logging, and log this
    fprintf(stderr, "Stack Overflow Error\n");
    exit(2);
  }
  stack->data[stack->pointer++] = x;
}

INTERNAL void
c8_stack_pop(struct c8_stack* stack) {
  if (stack->pointer == 0) {
    // stack underflow
    //TODO(bryan) add logging, and log this
    fprintf(stderr, "Stack Underflow Error\n");
    exit(2);
  }
  stack->pointer--;
}

INTERNAL C8_INT_16
c8_stack_top(struct c8_stack* stack) {
  return stack->data[stack->pointer];
}

INTERNAL void
c8_stack_dump(struct c8_stack* stack) {
  (void)stack; //TODO(bryan) implement
}

INTERNAL void
c8_reg_dump(struct c8_cpu* cpu) {
  (void)cpu; //TODO(bryan) implement
}

INTERNAL void
c8_mem_dump(struct c8_cpu* cpu) {
  //TODO(bryan) set up proper logging, and dump this to file
  C8_BYTE* ram = cpu->ram;
  int i;
  for (i = 1; i <= C8_RAM_SIZE; i++) {
    C8_INT_16 addr = ram[i] << 8 | ram[i + 1];
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

INTERNAL C8_INT_16
c8_fetch(struct c8_cpu* cpu) {
  C8_INT_16 pc = cpu->reg_pc;
  C8_BYTE* ram = cpu->ram;
  return ram[pc] << 8 | ram[pc + 1];
}

INTERNAL void
c8_decode(struct c8_cpu* cpu, C8_INT_16 op_code) {
  C8_INT_16 vx = op_code & 0x0F00 >> 8;
  C8_INT_16 vy = op_code & 0x00F0 >> 4;
  C8_INT_16 imm;
  C8_INT_16 addr;
  switch(op_code & AND_TOP_MSK) {
    case OP_0000:
      switch (op_code & AND_BOT_MSK) {
        case OP_CLR_SCN:
          //TODO(bryan) clear screen
          cpu->reg_pc += 2;
          break;
        case OP_SUB_RTN:
          cpu->reg_pc = c8_stack_top(&cpu->stack);
          c8_stack_pop(&cpu->stack);
          cpu->reg_pc += 2;
          break;
        default:
          //TODO(bryan) log error
          c8_mem_dump(cpu);
          exit(2);
          break;
      }
      break;
    case OP_JMP_ADR:
      addr = op_code & 0x0FFF;
      cpu->reg_pc = addr;
      break;
    case OP_CLL_SUB:
      c8_stack_push(&cpu->stack, cpu->reg_pc); 
      addr = op_code & 0x0FFF;
      cpu->reg_pc = addr;
      break;
    case OP_TST_EQ:
      imm = op_code & 0x00FF;
      if (cpu->reg_v[vx] == imm) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_TST_NEQ:
      imm = op_code & 0x00FF;
      if (cpu->reg_v[vx] != imm) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_EQ_EQ:
      if (cpu->reg_v[vx] == cpu->reg_v[vy]) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_SET_IMM:
      imm = op_code & 0x0FF;
      cpu->reg_v[vx] = imm;
      cpu->reg_pc += 2;
      break;
    case OP_ADD_IMM:
      imm = op_code & 0x00FF;
      cpu->reg_v[vx] += imm;
      cpu->reg_pc += 2;
      break;
    case OP_8000:
      // need to check right most bit
      switch (op_code & AND_BOT_MSK) {
        case OP_SET_REG:
          cpu->reg_v[vx] = cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_SET_OR:
          cpu->reg_v[vx] |= cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_SET_AND:
          cpu->reg_v[vx] &= cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_SET_XOR:
          cpu->reg_v[vx] ^= cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_ADD_REG:
          if (cpu->reg_v[vy] > (0xFF - cpu->reg_v[vx])) {
            cpu->reg_v[C8_CARRY] = 1;
          } else {
            cpu->reg_v[C8_CARRY] = 0;
          }
          cpu->reg_v[vx] += cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_X_SUB_Y:
          if (cpu->reg_v[vy] > cpu->reg_v[vx]) {
            cpu->reg_v[C8_CARRY] = 1;
          } else {
            cpu->reg_v[C8_CARRY] = 0;
          }
          cpu->reg_v[vx] -= cpu->reg_v[vy];
          cpu->reg_pc += 2;
          break;
        case OP_RS_REG:
          if (cpu->reg_v[vx] % 2 == 1) {
            cpu->reg_v[C8_CARRY] = 1;
          } else {
            cpu->reg_v[C8_CARRY] = 0;
          }
          cpu->reg_v[vx] >>= 1;
          cpu->reg_pc += 2;
          break;
        case OP_Y_SUB_X:
          if (cpu->reg_v[vx] > cpu->reg_v[vy]) {
            cpu->reg_v[C8_CARRY] = 1;
          } else {
            cpu->reg_v[C8_CARRY] = 0;
          }
          cpu->reg_v[vx] = cpu->reg_v[vy] - cpu->reg_v[vx];
          cpu->reg_pc += 2;
          break;
        case OP_LS_REG:
          if ((cpu->reg_v[vx] & 0x80) == 0x80) {
            cpu->reg_v[C8_CARRY] = 1; 
          } else {
            cpu->reg_v[C8_CARRY] = 0;
          }
          cpu->reg_v[vx] <<= 1;
          cpu->reg_pc += 2;
          break;
      } 
      break;
    case OP_NEQ_NEQ:
      if (cpu->reg_v[vx] != cpu->reg_v[vy]) {
        cpu->reg_pc += 2;
      }
      cpu->reg_pc += 2;
      break;
    case OP_SET_I:
      addr = op_code & 0x0FFF;
      cpu->reg_index = addr;
      cpu->reg_pc += 2;
      break;
    case OP_JMP_V0:
      addr = op_code & 0x0FFF;
      addr += cpu->reg_v[0];
      cpu->reg_pc = addr;
      break;
    case OP_SET_RND:
      addr = op_code & 0x00FF;
      //TODO(bryan) add addr with rand()
      cpu->reg_v[vx] = addr;
      cpu->reg_pc += 2;
      break;
    case OP_DRAW:
      //TODO(bryan) implement
      cpu->reg_pc += 2;
      break;
    case OP_E000:
      switch (op_code & AND_BOT_MSK) {
        case OP_KEY_DWN:
          if (cpu->keys[cpu->reg_v[vx]]) {
            cpu->reg_pc += 2;
          }
          cpu->reg_pc += 2;
          break;
        case OP_KEY_UP:
          if (!cpu->keys[cpu->reg_v[vx]]) {
            cpu->reg_pc += 2;
          }
          cpu->reg_pc += 2;
          break;
      }
      break;
    case OP_F000:
      switch (op_code & AND_EFF_MSK) {
        case OP_DLY_SET:
          break;
        case OP_KEY_PRS:
          break;
        case OP_SET_DLY:
          break;
        case OP_SET_SND:
          break;
        case OP_ADD_I:
          break;
        case OP_SET_SPRT:
          break;
        case OP_SET_BCD:
          break;
        case OP_STR:
          break;
        case OP_LD:
          break;
      }
      break;
  }
}

void
c8_cpu_cycle(struct c8_cpu* cpu) {

  C8_INT_16 op_code = c8_fetch(cpu);
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



