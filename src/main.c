#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> 
#include <stdlib.h>

#include "parse.h"
#include "global.h"

#define MAX_LINE_LENGTH 1024

// #define __DEBUG__

f_elem_t* f_elem;

FILE* object_fp;

void check_file_open (FILE* fp) 
{
        if (fp == NULL) {
                perror("open error!");
                exit(EXIT_FAILURE);
        }
}

void read_asm_file (FILE* fp)
{
        char buffer[MAX_LINE_LENGTH];

        while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
                // printf("%s", buffer);
                parse(f_elem, object_fp, buffer);
        }

        fseek(fp, 0, SEEK_SET);
        
        #ifdef __DEBUG__
        print_labels(f_elem->label_table);
        print_memory_seg(f_elem->vmem);
        #endif

        f_elem->vmem->data_tail = -1;
        f_elem->vmem->text_tail = -1;
        f_elem->mode_info->flag_label_read = (MODE_UNREAD_LABEL);
        
        
        
        while (fgets(buffer, MAX_LINE_LENGTH, fp) != NULL) {
                parse(f_elem, object_fp, buffer);
        }

        #ifdef __DEBUG
        print_labels(f_elem->label_table);
        print_memory_seg(f_elem->vmem);
        #endif

}

void init_environment ()
{
        f_elem = (f_elem_t*)malloc(sizeof(f_elem_t));
        init_mode_info(&f_elem->mode_info);
        init_vmem(&f_elem->vmem);
        init_label_table(&f_elem->label_table);
}

void destroy_environment ()
{
        destroy_vmem(f_elem->vmem);
        destroy_mode_info(f_elem->mode_info);
        destroy_label_table(f_elem->label_table);
        free(f_elem);
        
}

void write_obj_file () 
{
        _vmem_t* _vmem = f_elem->vmem;
        uint32_t text_section_size = (_vmem->text_tail + 1) * 4;
        uint32_t data_section_size = (_vmem->data_tail + 1) * 4;

        fprintf(object_fp, "0x%x\n", text_section_size);
        fprintf(object_fp, "0x%x\n", data_section_size);

        for (uint32_t i = _vmem->text_head; i <= _vmem->text_tail; i++) {
                fprintf(object_fp, "0x%x\n", _vmem->text_seg[i]);
        }
        for (uint32_t i = _vmem->data_head; i <= _vmem->data_tail; i++) {
                fprintf(object_fp, "0x%x\n", _vmem->data_seg[i]);
        }
}

int main(int argc, char**argv) {
        init_environment();
        char* tgt_file_name = argv[1]; 
        
        FILE* tgt_fp = fopen(tgt_file_name, "r");
        check_file_open(tgt_fp);

        char object_file_name[256];
        strcpy(object_file_name, argv[1]);

        object_file_name[strlen(object_file_name) - 2] = '.';
        object_file_name[strlen(object_file_name) - 1] = 'o';

        object_fp = fopen(object_file_name, "w");
        check_file_open(object_fp);

        read_asm_file(tgt_fp);
        write_obj_file();

        fclose(tgt_fp);
        fclose(object_fp);
        return 0;
}