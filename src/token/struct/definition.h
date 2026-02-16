

#ifndef C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H
#define C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H


#include "../../string/struct/definition.h"
#include "../../string/pointer/definition.h"
/**
 * @brief The minimal unit that the compiler understands
 */
typedef struct {
    STR_PTR _fpos;
    STRING _str;
    TKN_TYPE _type;
} TOKEN;



#endif


