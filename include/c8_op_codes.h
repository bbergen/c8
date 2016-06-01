#ifndef C8_OP_CODES_H
#define C8_OP_CODES_H

#define OP_CLR_SCN  0x00E0
#define OP_SUB_RTN  0x00EE

#define OP_JMP_ADR  0x1000
#define OP_CLL_SUB  0x2000
#define OP_TST_EQ   0x3000
#define OP_TST_NEQ  0x4000
#define OP_EQ_EQ    0x5000
#define OP_SET_IMM  0x6000
#define OP_ADD_IMM  0x7000

#define OP_SET_REG  0x8000
/*
* The following 8 op codes must be checked after OP_SET_REG
*/
#define OP_SET_OR   0x0001
#define OP_SET_AND  0x0002
#define OP_SET_XOR  0x0003
#define OP_ADD_REG  0x0004
#define OP_X_SUB_Y  0x0005
#define OP_RS_REG   0x0006
#define OP_Y_SUB_X  0x0007
#define OP_LS_REG   0x000E

#define OP_NEQ_NEQ  0x9000
#define OP_SET_IDX  0xA000
#define OP_JMP_V0   0xB000
#define OP_SET_RND  0xC000
#define OP_DRAW     0xD000

//TODO(bryan) define Es
//TODO(bryan define Fs

#endif
