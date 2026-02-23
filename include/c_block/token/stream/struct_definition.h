


#ifndef C_BLOCK_COMPILER_TOKEN_STREAM_DEF_H
#define C_BLOCK_COMPILER_TOKEN_STREAM_DEF_H


#include "c_block/token/struct_definition.h"


/**
 * @brief An array of tokens.
 */
typedef struct {
    TOKEN* _toks;
    size_t _buff;
    size_t _len;
} TOKEN_STREAM;

#define EMPTY_TOKEN_STREAM (TOKEN_STREAM) {._toks = nullptr, ._buff = 1, ._len = 0}



#endif


