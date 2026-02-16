

#ifndef C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H
#define C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H


#include "../../string/struct/definition.h"
#include "../../string/pointer/definition.h"

typedef enum {
    INVALID_STATE,
    RESERVED_WORD,
    SHY_IDENTIFIER,
    LOUD_IDENTIFIER,
    LITERAL,
    SINGLE_CHAR,
    BRACKET_OPEN,
    BRACKET_CLOSE,
    SINGLE_QUOTED_STRING,
    DOUBLE_QUOTED_STRING,
    NUMBER
} TKN_TYPE;




/**
 * @brief The minimal unit that the compiler understands
 */
typedef struct {
    STR_PTR _fpos;
    STRING _str;
    TKN_TYPE _type;
} TOKEN;



#define EMPTY_TOKEN (TOKEN) {._fpos = NULL, ._str = nullptr, ._type = INVALID_STATE}
#endif


