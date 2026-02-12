

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_H
#define C_BLOCK_COMPILER_STRING_STRUCT_H

#include <stddef.h>

typedef struct {
    char *str;
    size_t length;
    size_t buffer;
} STRING;

typedef enum {
    /// Good to continue.
    OK,

    /// Error, can't continue.
    ERR,

    /// memory allocation error
    ERR_MEM,

    /// Strings are not equal.
    DIFF
} STR_LOG;

#endif
