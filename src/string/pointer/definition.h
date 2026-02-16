

#ifndef C_BLOCK_COMPILER_STRING_POINTER_DEF_H
#define C_BLOCK_COMPILER_STRING_POINTER_DEF_H

#include <stddef.h>
#include "../struct/definition.h"

/**
 * @brief A fail-safe pointer to iterate in & out of a string struct.
 */
typedef struct {
    STRING* _str_struct;
    size_t _index;
    size_t _line;
    size_t _column;
} STR_PTR;

/**
 * @brief An initialiser macro helper for a null string pointer.
 */

#define NULL_STR_PTR (STR_PTR){._str_struct = nullptr, ._index = 0, ._line = 1, ._column = 1}


#endif