#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "global.h"


void init_label_table (label_t** table)
{
        label_t* tmp = (label_t*)malloc(sizeof(label_t));
        
        tmp->label = (char**)malloc(sizeof(char*) * (INIT_SIZE_LABEL_T));
        tmp->address = (uint32_t*)malloc(sizeof(uint32_t) * (INIT_SIZE_LABEL_T));
        
        tmp->tail = -1;
        tmp->doubling_limit = (INIT_SIZE_LABEL_T);

        *table = tmp;
}
void destroy_label_table(label_t* table) {
        for (uint32_t i = 0; i <= table->tail; ++i) {
                free(table->label[i]);
        }
        
        free(table->label);
        free(table->address);
}

void doubling_label_table(label_t* table) {
        uint32_t new_capacity = table->doubling_limit * 2;
        char** new_label = realloc(table->label, sizeof(char*) * new_capacity);
        uint32_t* new_address = realloc(table->address, sizeof(uint32_t) * new_capacity);
        
        table->doubling_limit = new_capacity;
        table->label = new_label;
        table->address = new_address;
}

void push_label (label_t* table, char* token, uint32_t offset)
{
        token[strlen(token) - 1] = '\0';
        if (++table->tail >= table->doubling_limit ) {
                doubling_label_table(table);
        }
        uint32_t tail = table->tail;

        table->label[tail] = (char*)malloc(sizeof(char) * strlen(token) + 1);
        memcpy(table->label[tail], token, strlen(token) + 1);

        table->address[tail] = offset;

        
}

uint32_t get_address (label_t* table, char* target)
{
        for (int i = 0; i <= table->tail; i++) {
                if(strcmp(table->label[i], target) != 0) {
                        continue;
                }
                return table->address[i];
        }
        
        return 0x00000000;
}

void print_labels (label_t* table) 
{
        for (int i = 0; i <= table->tail; i++) {
                printf("label %s : 0x%x\n", table->label[i], table->address[i]);
        }
}