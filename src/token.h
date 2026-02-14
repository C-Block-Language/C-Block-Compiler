
#ifndef C_BLOCK_COMPILER_TOKEN_H
#define C_BLOCK_COMPILER_TOKEN_H
#include "string_struct.h"

typedef struct {
    STR_PTR pos_in_file;
    STRING str;
} TOKEN;


typedef struct {
    TOKEN* pos_in_file;
    STRING str;
    size_t _buff;
} token;

#endif