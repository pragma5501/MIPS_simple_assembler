#ifndef __RFORM_H__
#define __RFORM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



#define ADDU    0x00
#define AND     0x00
#define JR      0x00
#define NOR     0x00
#define OR      0x00
#define SLTU    0x00
#define SLL     0x00
#define SRL     0x00
#define SUBU    0x00

#define RFORM_IDX_TYPE_OP 0xb
#define RFORM_IDX_TYPE_RS 0x1
#define RFORM_IDX_TYPE_RT 0xd
#define RFORM_IDX_TYPE_RD 0x3
#define RFORM_IDX_TYPE_SHAMT 0x4
#define RFORM_IDX_TYPE_FUNCT 0x5
#define RFORM_IDX_TYPE_F_NAN 0xc

typedef struct _RFORM {
        uint8_t op      : 6;
        uint8_t rs      : 5;
        uint8_t rt      : 5;
        uint8_t rd      : 5;
        uint8_t shamt   : 5;
        uint8_t funct   : 6;
} _rform_t;

void process_rform (_rform_t* rform, int idx_type, char* token);
uint32_t out_rform (_rform_t* rform);
#endif