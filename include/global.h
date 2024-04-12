#ifndef __GLOBAL_H__
#define __GLOBAL_H__


#include "vmemory.h"
#define INIT_SIZE_LABEL_T 10


typedef struct input_mode_t {
        uint8_t flag_label_read : 2;
        uint8_t flag_data_text  : 2;
        uint8_t flag_word       : 2;
        
} input_mode_t;

#define MODE_READ_LABEL 0x0
#define MODE_UNREAD_LABEL 0x1

typedef struct label_table_t {
        char** label;
        uint32_t* address;
        uint32_t tail;
        uint32_t doubling_limit;
} label_t;

typedef struct f_elem_t {
        input_mode_t* mode_info;
        _vmem_t* vmem;
        label_t* label_table;
} f_elem_t;

void init_label_table (label_t** table);
void destroy_label_table(label_t* table);
void push_label (label_t* table, char* token, uint32_t offset);
uint32_t get_address (label_t* table, char* target);
void print_labels (label_t* table) ;
#endif

