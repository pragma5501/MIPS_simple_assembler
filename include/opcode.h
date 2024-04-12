#ifndef __OPCODE_H__
#define __OPCODE_H__

#include "iform.h"
#include "jform.h"
#include "rform.h"

#include <stdint.h>
#include <string.h>

#define R_FORMAT 0x0
#define I_FORMAT 0x1
#define J_FORMAT 0x2

#define F_NAN   0xc
#define RS      0x1
#define RT      0xd
#define RD      0x3
#define SHAMT   0x4
#define FUNCT   0x5
#define IMM     0x6
#define LABEL   0x7
#define JTARGET 0x9
#define OFFSET  0xa
#define OPCODE  0xb

#define IDX_INST        0
#define IDX_OPCODE      1
#define IDX_FORMAT      2
#define IDX0            3
#define IDX1            4
#define IDX2            5
#define IDX3            6
#define IDX4            7
#define IDX5            8

#define IDX_OFFSET      3

typedef struct inst_opcode_pair{
        char* inst;
        uint8_t opcode  : 6;
        uint8_t format  : 6;
        uint8_t idx0    : 6;
        uint8_t idx1    : 4;
        uint8_t idx2    : 4;     
        uint8_t idx3    : 4;
        uint8_t idx4    : 4;
        uint8_t idx5    : 6;
} inst_opcode_pair_t;





static const inst_opcode_pair_t map_inst_opcode[] = {
        {"addiu", ADDIU, I_FORMAT, OPCODE, RT,      RS,     IMM,   F_NAN, F_NAN},
        {"addu",  ADDU , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x21 },
        {"and",   AND  , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x24 },
        {"andi",  ANDI , I_FORMAT, OPCODE, RT,      RS,     IMM,   F_NAN, F_NAN},
        {"beq",   BEQ  , I_FORMAT, OPCODE, RS,      RT,     LABEL, F_NAN, F_NAN},
        {"bne",   BNE  , I_FORMAT, OPCODE, RS,      RT,     LABEL, F_NAN, F_NAN},
        {"j",     J    , J_FORMAT, OPCODE, JTARGET, F_NAN,  F_NAN, F_NAN, F_NAN},
        {"jal",   JAL  , J_FORMAT, OPCODE, JTARGET, F_NAN,  F_NAN, F_NAN, F_NAN},
        {"jr",    JR   , R_FORMAT, OPCODE, RS,      F_NAN,  F_NAN, F_NAN, 0x08 },
        {"lui",   LUI  , I_FORMAT, OPCODE, RT,      IMM,    F_NAN, F_NAN, F_NAN},
        {"lw",    LW   , I_FORMAT, OPCODE, RT,      IMM, RS,    F_NAN, F_NAN},
        {"lb",    LB   , I_FORMAT, OPCODE, RT,      IMM, RS,    F_NAN, F_NAN},
        {"nor",   NOR  , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x27 },
        {"or",    OR   , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x25 },
        {"ori",   ORI  , I_FORMAT, OPCODE, RT,      RS,     IMM,   F_NAN, F_NAN},
        {"sltiu", SLTIU, I_FORMAT, OPCODE, RT,      RS,     IMM,   F_NAN, F_NAN},
        {"sltu",  SLTU , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x2b },
        {"sll",   SLL  , R_FORMAT, OPCODE, RD,      RT,     SHAMT, F_NAN, 0x00 },
        {"srl",   SRL  , R_FORMAT, OPCODE, RD,      RT,     SHAMT, F_NAN, 0x02 },
        {"sw",    SW   , I_FORMAT, OPCODE, RT,      IMM, RS,    F_NAN, F_NAN},
        {"sb",    SB   , I_FORMAT, OPCODE, RT,      IMM, RS,    F_NAN, F_NAN},
        {"subu",  SUBU , R_FORMAT, OPCODE, RD,      RS,     RT,    F_NAN, 0x23 },
        {"la",    LA   , LA_FORM , OPCODE, RT,      OFFSET, F_NAN, F_NAN, F_NAN}
};

int get_inst_map_idx (char* instruction);

int get_idx_type (int map_idx, int idx_cnt);


#endif