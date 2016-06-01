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

//TODO(bryan) define 8s

#define OP_NEQ_NEQ  0x9000
#define OP_SET_I    0xA000
#define OP_JMP_V0   0xB000
#define OP_SET_RND  0xC000
#define OP_DRAW     0xD000

//TODO(bryan) define Es
//TODO(bryan define Fs

#endif
