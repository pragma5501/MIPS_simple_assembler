

#include "opcode.h"

#define MAP_INST_OPCODE_LEN 23



int get_inst_map_idx (char* instruction)
{
        for (int i = 0; i < (MAP_INST_OPCODE_LEN); i++) {
                if (strcmp(map_inst_opcode[i].inst, instruction) == 0) {
                        return i;
                }
        }
}

int get_idx_type (int map_idx, int idx_cnt)
{
        idx_cnt = (IDX_OFFSET) + idx_cnt;

        switch (idx_cnt)
        {
        case IDX0:
                return map_inst_opcode[map_idx].idx0;
        case IDX1:
                return map_inst_opcode[map_idx].idx1;
        case IDX2:
                return map_inst_opcode[map_idx].idx2;
        case IDX3:
                return map_inst_opcode[map_idx].idx3;
        case IDX4:
                return map_inst_opcode[map_idx].idx4;
        case IDX5:
                return map_inst_opcode[map_idx].idx5;
        }
}

