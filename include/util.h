#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h> 


#define TYPE_HEX 0x00
#define TYPE_DEC 0x01

int is_hex (char* token);

#endif