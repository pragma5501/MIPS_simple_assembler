#include "util.h"


int is_hex (char* token) 
{
        if (strlen(token) < 2) {
                return (TYPE_DEC);
        }
        if (token[0] == '0' && token[1] == 'x') {
                return (TYPE_HEX);
        }
        return (TYPE_DEC);
}