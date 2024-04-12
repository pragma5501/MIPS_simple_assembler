#include "parse.h"


input_mode_t* mode_info;

void init_parse_inst_elem_t (parse_inst_elem_t* elem) 
{

        elem->idx_cnt = 0;
        elem->type = (TYPE_NONE);
        

        elem->rform = (_rform_t*)malloc(sizeof(_rform_t));
        elem->iform = (_iform_t*)malloc(sizeof(_iform_t));
        elem->jform = (_jform_t*)malloc(sizeof(_jform_t));
        

        memset(elem->rform, 0, sizeof(_rform_t));
        memset(elem->iform, 0, sizeof(_iform_t));
        memset(elem->jform, 0, sizeof(_jform_t));

        elem->laform = (_la_form_t*)malloc(sizeof(_la_form_t));
        elem->laform->lui_inst = (_iform_t*)malloc(sizeof(_iform_t));
        elem->laform->ori_inst = (_iform_t*)malloc(sizeof(_iform_t));

        memset(elem->laform->lui_inst, 0, sizeof(_iform_t));
        memset(elem->laform->ori_inst, 0, sizeof(_iform_t));
}

void destroy_parse_inst_elem_t (parse_inst_elem_t* elem)
{
        free(elem->rform);
        free(elem->iform);
        free(elem->jform);

        free(elem->laform->lui_inst);
        free(elem->laform->ori_inst);
        free(elem->laform);

        free(elem);
}


void parse (f_elem_t* f_elem, FILE* object_fp, char* instruction) 
{       
        parse_inst_elem_t* elem = (parse_inst_elem_t*)malloc(sizeof(parse_inst_elem_t));
        init_parse_inst_elem_t(elem);

        const char* delimiter = ",\n() \0";
        char* token;
        char temp[strlen(instruction) + 2];
        strcpy(temp, instruction);

        token = strtok(temp, delimiter);

        while (token != NULL) {
                
                int tmp = classify_token_type(token, strlen(token));
                elem->token = token;

                if (elem->type == (TYPE_NONE) || elem->type == (TYPE_LABEL)) {
                        elem->type = tmp;
                        elem->idx_cnt = 0;
                }
                
                process_token(f_elem, elem);
                elem->idx_cnt++;
                

                token = strtok(NULL, delimiter);

        }
        switch (mode_info->flag_data_text) {
        case (MODE_DATA):
                transfer_word_to_32bit(f_elem, elem);
                break;
        case (MODE_TEXT):
                transfer_form_to_32bit(f_elem, elem);
                break;
        }
        
        destroy_parse_inst_elem_t(elem);
        
}

uint32_t transfer_form_to_32bit (f_elem_t* f_elem, parse_inst_elem_t* elem) 
{
        if (elem->idx_cnt < 2) return 0;
        if (mode_info->flag_label_read == (MODE_READ_LABEL)) {
                f_elem->vmem->text_tail++;
                return 0;
        }

        uint32_t inst32;
        
        switch (elem->format) {
        case (R_FORMAT):
                inst32 = out_rform(elem->rform);
                break;
        case (I_FORMAT):
                inst32 = out_iform(elem->iform);
                break;
        case (J_FORMAT):
                inst32 = out_jform(elem->jform);
                break;
        case (LA_FORM):
                inst32 = out_iform(elem->laform->lui_inst);
                
                if (elem->laform->ori_inst->offset > 0x0000 ) {
                        push_text_seg(f_elem->vmem, inst32);
                        inst32 = out_iform(elem->laform->ori_inst);
                }
                break;
        
        }
        push_text_seg(f_elem->vmem, inst32);

}

uint32_t transfer_word_to_32bit (f_elem_t* f_elem, parse_inst_elem_t* elem)
{
        if (elem->idx_cnt < 2) {
                return 0;
        }
        if (mode_info->flag_label_read == (MODE_READ_LABEL)) {
                f_elem->vmem->data_tail++;
                return 0;
        }

        char* directive = elem->token;

        uint32_t word32;
        if (is_hex(directive) == (TYPE_HEX)) {
                word32 = strtoul(directive + 2, NULL, 16);
        } else {
                word32 = (uint32_t)atoi(directive);
        }
        push_data_seg(f_elem->vmem, word32);
}

int classify_token_type (char* token, int len_tok)
{
        if (token[len_tok - 1] == ':') {
                return TYPE_LABEL;
        }
        if (token[0] == '.') {
                return TYPE_DIRECTIVE;
        }
        if (token[0] >= 97 && token[0] <= 122) {
                return TYPE_OPCODE;
        }
        return TYPE_NONE;

}

void process_token (f_elem_t *f_elem, parse_inst_elem_t* elem) 
{
        switch (elem->type) {
        case (TYPE_LABEL):
                process_label(f_elem, elem->token);
                break;
        case (TYPE_DIRECTIVE):
                process_directives(f_elem, elem);
                break;
        case (TYPE_OPCODE):
                process_opcode(f_elem, elem);
                break;
        }
}

void process_label (f_elem_t* f_elem, char* token)
{
        uint32_t offset;

        switch (mode_info->flag_data_text) {
        case (MODE_DATA):
                offset = (DATA_SEG_OFFSET) + (f_elem->vmem->data_tail * 4) + 4;
                break;

        case (MODE_TEXT):
                offset = (TEXT_SEG_OFFSET) + (f_elem->vmem->text_tail *4) + 4;
                break;
        }
        push_label(f_elem->label_table, token, offset);
        
}

void process_directives (f_elem_t *f_elem, parse_inst_elem_t* elem)
{
        char* directive = elem->token;

        
        if (strcmp(directive, ".data") == 0) {
                mode_info->flag_data_text = (MODE_DATA);
        }
        if (strcmp(directive, ".text") == 0) {
                mode_info->flag_data_text = (MODE_TEXT);
        }

        if (strcmp(directive, ".word") == 0) {
                mode_info->flag_word = (MODE_WORD);
        }
}       

void process_opcode (f_elem_t* f_elem, parse_inst_elem_t* elem)
{
        // case : instruction name
        if (elem->idx_cnt == 0) {
                char temp[strlen(elem->token) + 2];
                strcpy(temp, elem->token);
                elem->inst_map_idx = get_inst_map_idx(elem->token);
                elem->format = map_inst_opcode[elem->inst_map_idx].format;

                sprintf(temp, "%d", map_inst_opcode[elem->inst_map_idx].opcode);
                process_formating(f_elem, elem, temp);

                elem->idx_cnt = (IDX5) - (IDX_OFFSET);
                sprintf(temp, "%d", map_inst_opcode[elem->inst_map_idx].idx5);
                process_formating(f_elem, elem, temp);
                
                elem->idx_cnt = 0;
                return;
        }
        
        process_formating(f_elem, elem, elem->token);
}

void process_formating (f_elem_t* f_elem, parse_inst_elem_t* elem, char* token)
{

        int idx_type = get_idx_type(elem->inst_map_idx, elem->idx_cnt);

        switch (elem->format) {
        case (LA_FORM):
                process_laform(f_elem, elem->laform, idx_type, token);
                break;
        case (RFORM):
                process_rform(elem->rform, idx_type, token);
                break;
        case (IFORM):
                process_iform(f_elem, elem->iform, idx_type, token);
                break;
        case (JFORM):
                process_jform(f_elem, elem->jform, idx_type, token);
                break;
        }
}


void init_mode_info (input_mode_t** _mode_info)
{
        mode_info = (input_mode_t*)malloc(sizeof(input_mode_t));
        mode_info->flag_label_read = MODE_READ_LABEL;
        mode_info->flag_data_text = MODE_NONE;
        mode_info->flag_word      = MODE_NONE;
        *_mode_info = mode_info;
}

void destroy_mode_info (input_mode_t* _mode_info)
{
        free(mode_info);
}

