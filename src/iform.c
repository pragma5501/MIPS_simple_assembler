#include "iform.h"
#include "util.h"

void process_laform (f_elem_t* f_elem, _la_form_t* laform, int idx_type, char* token) 
{
        if (token[0] == '$') {
                token = token + 1;
        }
        
        switch (idx_type) {
        case IFORM_IDX_TYPE_OP:
                laform->lui_inst->op = LUI;
                laform->ori_inst->op = ORI;
                break;
        case IFORM_IDX_TYPE_RT:
                laform->lui_inst->rt = (uint8_t)atoi(token);
                laform->ori_inst->rt = (uint8_t)atoi(token);
                laform->ori_inst->rs = (uint8_t)atoi(token);
                break;
        case IFORM_IDX_TYPE_OFFSET:;

                uint32_t offset = get_address(f_elem->label_table, token);
                if (offset == 0x00000000) {
                        break;
                        //exit(0);
                }
                laform->lui_inst->offset = offset >> 16;
                laform->ori_inst->offset = offset;
                
                break;
        }
}

void process_iform (f_elem_t* f_elem, _iform_t* iform, int idx_type, char* token)
{
        if (token[0] == '$') {
                token = token + 1;
        }

        uint8_t idx = (uint8_t)atoi(token);

        switch (idx_type) {
        case IFORM_IDX_TYPE_F_NAN :
                break;

        case IFORM_IDX_TYPE_OP:
                iform->op = (uint8_t)idx;
                break;
        case IFORM_IDX_TYPE_RS:
                iform->rs = (uint8_t)idx;
                break;
        case IFORM_IDX_TYPE_RT:
                iform->rt = (uint8_t)idx;
                break;
        case IFORM_IDX_TYPE_OFFSET:;
                iform->offset = strtoul(token + 2, NULL, 16);
                break;

        case IFORM_IDX_TYPE_IMM:;
                uint16_t imm;
                if (is_hex(token) == (TYPE_HEX)) {
                        imm = strtoul(token + 2, NULL, 16);
                } else {
                        imm = (uint16_t)atoi(token);
                }
                iform->offset = imm;
                break;

        case IFORM_IDX_TYPE_LABEL:;
                uint32_t offset = get_address(f_elem->label_table, token) / 4;
                iform->offset = offset;
                if (offset == 0x00000000) {
                        //exit(0);
                }
                break;
        }

}

uint32_t out_iform (_iform_t* iform)
{
        uint32_t out = 0;
        out += ((uint32_t)iform->op) << (26);
        out += ((uint32_t)iform->rs) << (21);
        out += ((uint32_t)iform->rt) << (16);
        out += ((uint32_t)iform->offset);

        return out;
}
