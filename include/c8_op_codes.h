#ifndef C8_OP_CODES_H
#define C8_OP_CODES_H

#define AND_TOP_MSK 0xF000  // Use to mask opcode during decode
#define AND_BOT_MSK 0x000F  // Use to mask opcode during secondary decode
#define AND_EFF_MSK 0x00FF  // Use to mask opcode during secondary F decode

#define OP_0000     0x0000  // Refer to right bit checks below

#define OP_CLR_SCN  0x0000  // 0x00E0 - Clears the screen
#define OP_SUB_RTN  0x000E  // 0x00EE - Returns from subroutine 

#define OP_JMP_ADR  0x1000  // 0x1NNN - Jumps to address NNN 
#define OP_CLL_SUB  0x2000  // 0x2NNN - Calls routine at NNN
#define OP_TST_EQ   0x3000  // 0x3XNN - Skips next op if VX == NN
#define OP_TST_NEQ  0x4000  // 0x4XNN - Skips next op if VX != NN
#define OP_EQ_EQ    0x5000  // 0x5XY0 - Skips next op if VX == VY
#define OP_SET_IMM  0x6000  // 0x6XNN - Sets VX to NN
#define OP_ADD_IMM  0x7000  // 0x7XNN - Adds NN to VX

#define OP_8000     0x8000  // Refer to right bit checks below 

#define OP_SET_REG  0x0000  // 0x8XY0 - Sets VX to VY 
#define OP_SET_OR   0x0001  // 0x8XY1 - Sets VX to (VX | VY)
#define OP_SET_AND  0x0002  // 0x8XY2 - Sets VX to (VX & VY)
#define OP_SET_XOR  0x0003  // 0x8XY3 - Sets VX to (VX ^ VY)
#define OP_ADD_REG  0x0004  // 0x8XY4 - Adds VY to VX (VF set when carry)
#define OP_X_SUB_Y  0x0005  // 0x8XY5 - VY subbed from VX (VF set 0 on borrow)
#define OP_RS_REG   0x0006  // 0x8XY6 - VX >> 1 (VF set to lsb prior to shift)
#define OP_Y_SUB_X  0x0007  // 0x8XY7 - Set VX to (VY - VX) (VF 0 on borrow)
#define OP_LS_REG   0x000E  // 0x8XYE - VX << 1 (VF set to msb prior to shift)

#define OP_NEQ_NEQ  0x9000  // 0x9XY0 - Skip next op if VX != VY
#define OP_SET_IDX  0xA000  // 0xANNN - Sets I to address NNN
#define OP_JMP_V0   0xB000  // 0xBNNN - Jumps to address (NNN + V0)
#define OP_SET_RND  0xC000  // 0xCXNN - Set VX to (rand() & NN)
#define OP_DRAW     0xD000  // 0xDXYN - Draw to screen (See Notes)

#define OP_E000     0xE000  // Refer to right bit checks below

#define OP_KEY_DWN  0x000E  // 0xEX9E - Skip next op if key in VX is down
#define OP_KEY_UP   0x0001  // 0xEXA1 - Skip next op if key in VX isnt down

#define OP_F000     0xF000  // Refer to right bit checks below

#define OP_DLY_SET  0x0007  // 0xFX07 - Set VX to reg_delay_timer
#define OP_KEY_PRS  0x000A  // 0xFX0A - Wait for key press, store in VX
#define OP_SET_DLY  0x0015  // 0xFX15 - Set reg_delay_timer to VX
#define OP_SET_SND  0x0018  // 0xFX18 - Set reg_sound_timer to Vx
#define OP_ADD_I    0x001E  // 0xFX1E - Adds VX to reg_index
#define OP_SET_SPRT 0x0029  // 0xFX29 - Sets reg_index to sprite addr in VX
#define OP_SET_BCD  0x0033  // 0xFX33 - Sets I to BCD of VX (See Notes)
#define OP_STR      0x0055  // 0xFX55 - Stores V0 - VX in mem, starting at I
#define OP_LD       0x0065  // 0xFX65 - Fills V0 - Vx from mem, starting at I

#endif
