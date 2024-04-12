#include "vmemory.h"


void init_vmem (_vmem_t** vmem) 
{
        _vmem_t* _vmem = (_vmem_t*)malloc(sizeof(_vmem_t));
        _vmem->text_seg = (uint32_t*)malloc(sizeof(uint32_t) * (SEG_INIT_SIZE));
        _vmem->data_seg = (uint32_t*)malloc(sizeof(uint32_t) * (SEG_INIT_SIZE));
        _vmem->stack_seg = (uint32_t*)malloc(sizeof(uint32_t) * (SEG_INIT_SIZE));

        _vmem->text_head = 0;
        _vmem->text_tail = -1;

        _vmem->data_head = 0;
        _vmem->data_tail = -1;

        _vmem->stack_head = 0;
        _vmem->stack_tail = -1;

        _vmem->doubling_limit = (SEG_INIT_SIZE);

        *vmem = _vmem;
}

void destroy_vmem (_vmem_t* vmem)
{
        free(vmem->text_seg);
        free(vmem->data_seg);
        free(vmem->stack_seg);
        
        free(vmem);
}

void doubling (uint32_t** seg, int size) 
{
        uint32_t* new_seg = (uint32_t*)realloc(seg, sizeof(uint32_t) * size * 2);
        *seg = new_seg;
        

}

void push_data_seg (_vmem_t* vmem, uint32_t data)
{
        vmem->data_tail++;
        if (vmem->data_tail >= vmem->doubling_limit) {
                doubling(&vmem->data_seg, vmem->data_tail + 1);
                vmem->doubling_limit *= 2;
        }

        vmem->data_seg[vmem->data_tail] = data;
}

void push_text_seg (_vmem_t* vmem, uint32_t data)
{
        vmem->text_tail++;
        if (vmem->text_tail >= vmem->doubling_limit) {
                doubling(&vmem->text_seg, vmem->text_tail + 1);
                vmem->doubling_limit *= 2;
        }
        vmem->text_seg[vmem->text_tail] = data;
}

void push_stack_seg (_vmem_t* vmem, uint32_t data)
{
        vmem->stack_tail++;
        if (vmem->stack_tail >= vmem->doubling_limit) {
                doubling(&vmem->stack_seg, vmem->stack_tail + 1);
                vmem->doubling_limit *= 2;
        }

        vmem->stack_seg[vmem->stack_tail] = data;
}

void print_memory_seg (_vmem_t* vmem) 
{
        for (int i = vmem->data_head; i <= vmem->data_tail; i++) {
                printf("data seg %d : 0x%x\n", i, vmem->data_seg[i]);
        }
        for (int i = vmem->text_head; i <= vmem->text_tail; i++) {
                printf("text seg %d : 0x%x\n", i, vmem->text_seg[i]);
        }
}