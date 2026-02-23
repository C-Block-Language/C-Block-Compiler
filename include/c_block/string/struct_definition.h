
#ifndef C_BLOCK_COMPILER_STRING_STRUCT_DEF_H
#define C_BLOCK_COMPILER_STRING_STRUCT_DEF_H


#include <stddef.h>


/**
 * @brief An abstraction of char arrays ready for arbitrary long strings.
 */
typedef struct {
    char* _str;
    size_t _len;
    size_t _buff;
} STRING;


/**
 * @brief An initialiser macro helper for an empty string struct.
 */
#define EMPTY_STR (STRING){._str = nullptr, ._buff = 1, ._len = 0}

#define STATIC_STR(x) (STRING){._str = (x), ._len = sizeof(x) - 1, ._buff = 0}

#endif


