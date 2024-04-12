#ifndef __IFORM_H__
#define __IFORM_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "global.h"

#define IFORM_OFFSET 0x09

#define ADDIU   0x09
#define ANDI    0x0c
#define BEQ     0x04
#define BNE     0x05
#define LUI     0x0f
#define LW      0x23
#define ORI     0x0d
#define SLTIU   0x0b
#define SW      0x2b
#define LB      0x20
#define SB      0x28

#define LA      0x01
#define LA_FORM 0x11


#define IFORM_IDX_TYPE_OP       0xb
#define IFORM_IDX_TYPE_RS       0x1
#define IFORM_IDX_TYPE_RT       0xd
#define IFORM_IDX_TYPE_OFFSET   0xa
#define IFORM_IDX_TYPE_IMM      0x6
#define IFORM_IDX_TYPE_LABEL    0x7
#define IFORM_IDX_TYPE_F_NAN    0xc

typedef struct _IFORM {
        uint8_t op      : 6;
        uint8_t rs      : 5;
        uint8_t rt      : 5;
        uint16_t offset : 16;
} _iform_t;

typedef struct _LA_FORM {
        _iform_t* lui_inst;
        _iform_t* ori_inst;
        uint8_t flag_ori;
} _la_form_t;

#define MODE_LA_ORI 0x0
#define MODE_LA_ORI_NONE 0x1

void process_iform (f_elem_t* f_elem, _iform_t* iform, int idx_type, char* token);
uint32_t out_iform (_iform_t* iform);

void process_laform (f_elem_t* f_elem, _la_form_t* laform, int idx_type, char* token);

#endif