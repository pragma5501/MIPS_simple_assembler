#include "jform.h"
#include "global.h"


void process_jform (f_elem_t* f_elem, _jform_t* jform, int idx_type, char* token)
{

        switch (idx_type) {
        case JFORM_IDX_TYPE_F_NAN:
                break;
        case JFORM_IDX_TYPE_OP:;
                uint8_t idx = (uint8_t)atoi(token);
                jform->op = idx;
                break;

        case JFORM_IDX_TYPE_OFFSET:;
                uint32_t offset;
                if (token[0] == '0') {
                        offset = strtoul(token + 2, NULL, 16) / 4;
                } else {
                        offset = get_address(f_elem->label_table, token) / 4;
                        
                        if (offset == 0x00000000) {
                                
                                //exit(0);
                        }
                }
                jform->offset = offset;
                break;

        }
}


uint32_t out_jform (_jform_t* jform)
{
        uint32_t out = 0;
        out += ((uint32_t)jform->op) << (26);
        out += ((uint32_t)jform->offset);

        return out;
}

