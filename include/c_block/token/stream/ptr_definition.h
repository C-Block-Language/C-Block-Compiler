

#ifndef C_BLOCK_COMPILER_TOKEN_STREAM_PTR_DEF_H
#define C_BLOCK_COMPILER_TOKEN_STREAM_PTR_DEF_H


#include "c_block/token/stream/struct_definition.h"

/**
 * @brief A fail-safe pointer to iterate in & out of a token stream.
 */
typedef struct {
    TOKEN_STREAM* _tkn_strm;
    size_t _index;
} TKN_STREAM_PTR;

#define NULL_TOKEN_STREAM_PTR (TKN_STREAM_PTR) {_tkn_strm = nullptr, _index = 0}

#endif


