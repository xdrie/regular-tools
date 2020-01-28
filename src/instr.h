/*
instr.h
provides instruction declarations
*/

#pragma once

typedef char OPCODE;
typedef char ARG;

typedef struct {
    OPCODE opcode;
    ARG a1, a2, a3;
} Statement;

// opcodes
#define OP_NOP 0x00
#define OP_ADD 0x01
#define OP_SUB 0x02
#define OP_AND 0x03
#define OP_ORR 0x04
#define OP_XOR 0x05
#define OP_NOT 0x06
#define OP_LSH 0x07
#define OP_ASH 0x08
#define OP_TCU 0x09
#define OP_TCS 0x0a
#define OP_SET 0x0b
#define OP_MOV 0x0c
#define OP_LDW 0x0d
#define OP_STW 0x0e
#define OP_LDB 0x0f
#define OP_STB 0x10

// registers
#define REG_RPC 0x70
#define REG_R01 0x71
#define REG_R02 0x72
#define REG_R03 0x73
#define REG_R04 0x74
#define REG_R05 0x75
#define REG_R06 0x76
#define REG_R07 0x77
#define REG_R08 0x78
#define REG_R09 0x79
#define REG_R10 0x7a
#define REG_R11 0x7b
#define REG_R12 0x7c
#define REG_R13 0x7d
#define REG_R14 0x7e
#define REG_R15 0x7f
#define REG_R16 0x80
#define REG_R17 0x81
#define REG_R18 0x82
#define REG_R19 0x83
#define REG_R20 0x84
#define REG_R21 0x85
#define REG_R22 0x86
#define REG_R23 0x87
#define REG_R24 0x88
#define REG_R25 0x89
#define REG_R26 0x8a
#define REG_R27 0x8b
#define REG_R28 0x8c
#define REG_R29 0x8d
#define REG_RSP 0x8e
#define REG_RAT 0x8f
