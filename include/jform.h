#ifndef __JFORM_H__
#define __JFORM_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"

#define J       0x02
#define JAL     0x03

#define JFORM_IDX_TYPE_OP 0xb
#define JFORM_IDX_TYPE_OFFSET 0x9
#define JFORM_IDX_TYPE_F_NAN 0xc

typedef struct _JFORM {
        uint8_t op      : 6;
        uint32_t offset  : 26;
} _jform_t;

void process_jform (f_elem_t* f_elem, _jform_t* jform, int idx_type, char* token);
uint32_t out_jform (_jform_t* jform);

#endif