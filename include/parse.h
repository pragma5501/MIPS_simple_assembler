#ifndef __PARSE_H__
#define __PARSE_H__

#include "global.h"
#include "opcode.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h> 

#include "iform.h"
#include "rform.h"
#include "jform.h"

#include "util.h"

#define TYPE_LABEL      0x00
#define TYPE_DIRECTIVE  0x01
#define TYPE_OPERAND    0x02
#define TYPE_REGISTER   0x03
#define TYPE_CONSTANT   0x04
#define TYPE_WORD       0x05
#define TYPE_OPCODE     0x06
#define TYPE_NONE       0x07



#define MODE_NONE       0x0
#define MODE_DATA       0x1
#define MODE_TEXT       0x2
#define MODE_WORD       0x3



typedef struct parse_inst_elem_t {
        char* token;
        int type;
        int inst_map_idx;
        int idx_cnt;
        int format;

        _rform_t* rform;
        _iform_t* iform;
        _jform_t* jform;
        _la_form_t* laform;

} parse_inst_elem_t;



#define RFORM 0x0
#define IFORM 0x1
#define JFORM 0x2

void parse (f_elem_t* f_elem, FILE* object_fp, char* instruction);


int classify_token_type (char* token, int len_tok);
void process_token (f_elem_t *f_elem, parse_inst_elem_t* elem);
void process_directives (f_elem_t *f_elem, parse_inst_elem_t* elem);
void process_opcode (f_elem_t* f_elem, parse_inst_elem_t* elem);

void init_mode_info (input_mode_t** mode_info);
void destroy_mode_info (input_mode_t* _mode_info);

void process_formating (f_elem_t* f_elem, parse_inst_elem_t* elem, char* token);

uint32_t transfer_word_to_32bit (f_elem_t* f_elem, parse_inst_elem_t* elem);
uint32_t transfer_form_to_32bit (f_elem_t* f_elem, parse_inst_elem_t* elem);
void process_label (f_elem_t* f_elem, char* token);



#endif