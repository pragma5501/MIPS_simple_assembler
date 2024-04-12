#include "rform.h"

void process_rform (_rform_t* rform, int idx_type, char* token)
{
        if (token[0] == '$') {
                token = token + 1;
        }

        uint8_t idx = (uint8_t)atoi(token);
        switch (idx_type) {
        case RFORM_IDX_TYPE_F_NAN:
                break;
        case RFORM_IDX_TYPE_OP:
                rform->op = idx;
                break;
        case RFORM_IDX_TYPE_RS:
                rform->rs = idx;
                break;
        case RFORM_IDX_TYPE_RT:
                rform->rt = idx;
                break;
        case RFORM_IDX_TYPE_RD:
                rform->rd = idx;
                break;
        case RFORM_IDX_TYPE_SHAMT:
                rform->shamt = idx;
                break;
        default:
                rform->funct = idx;
                break;
        }
}

uint32_t out_rform (_rform_t* rform)
{
        uint32_t out = 0;
        out += ((uint32_t)rform->op) << (26);
        out += ((uint32_t)rform->rs) << (21);
        out += ((uint32_t)rform->rt) << (16);
        out += ((uint32_t)rform->rd) << (11);
        out += ((uint32_t)rform->shamt) << (6);
        out += ((uint32_t)rform->funct);


        return out;
}

