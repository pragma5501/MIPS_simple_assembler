#ifndef __VMEMORY_H__
#define __VMEMORY_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define DATA_SEG_OFFSET  0x10000000
#define TEXT_SEG_OFFSET  0x00400000
#define STACK_SEG_OFFSET 0x7ffffffc

#define SEG_INIT_SIZE 100

typedef struct virtual_memory {
        uint32_t* text_seg;
        uint32_t* data_seg;
        uint32_t* stack_seg;

        uint32_t text_head;
        uint32_t text_tail;
        uint32_t data_head;
        uint32_t data_tail;
        uint32_t stack_head;
        uint32_t stack_tail;

        uint32_t doubling_limit;
} _vmem_t;

void init_vmem (_vmem_t** vmem);
void destroy_vmem (_vmem_t* vmem);
void doubling (uint32_t** seg, int size) ;
void push_data_seg (_vmem_t* vmem, uint32_t data);
void push_text_seg (_vmem_t* vmem, uint32_t data);
void push_stack_seg (_vmem_t* vmem, uint32_t data);
void print_memory_seg (_vmem_t* vmem);

#endif