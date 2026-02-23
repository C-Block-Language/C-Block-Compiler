

#ifndef C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H
#define C_BLOCK_COMPILER_TOKEN_STRUCT_DEF_H


#include "c_block/string/ptr_definition.h"
#include "c_block/string/struct_definition.h"
#include "c_block/file/id_definition.h"


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
    FILE_ID _forigin;
    TKN_TYPE _type;
} TOKEN;



#define EMPTY_TOKEN (TOKEN) {._fpos = NULL, ._str = nullptr, ._type = INVALID_STATE, ._forigin = 0}


const static STRING reserved_words[] = {
    // Reserve all modifier execute sub-commands
    STATIC_STR("execute"),
    STATIC_STR("if"),
    STATIC_STR("align"),
    STATIC_STR("anchored"),
    STATIC_STR("as"),
    STATIC_STR("at"),
    STATIC_STR("facing"),
    STATIC_STR("in"),
    STATIC_STR("on"),
    STATIC_STR("positioned"),
    STATIC_STR("rotated"),
    STATIC_STR("summon"),
    STATIC_STR("run"),

    // reserve return keyword
    STATIC_STR("return"),

    // reserve native command keyword
    STATIC_STR("native"),
    // return function return types
    STATIC_STR("void"),
    STATIC_STR("int"),

    // reserve NBT path sources
    STATIC_STR("nbt_path"),
    STATIC_STR("entity"),
    STATIC_STR("storage"),
    STATIC_STR("block"),

    // reserve score variable type
    STATIC_STR("score"),

    // reserve nbt operations
    STATIC_STR("append"),
    STATIC_STR("insert"),
    STATIC_STR("merge"),
    STATIC_STR("prepend"),
    STATIC_STR("set"),
    STATIC_STR("remove"),

    // reserve NBT numeric data types
    STATIC_STR("byte"),
    STATIC_STR("short"),
    STATIC_STR("int"),
    STATIC_STR("long"),
    STATIC_STR("float"),
    STATIC_STR("double"),

    // reserve int_cast for casting NBT values to ints
    STATIC_STR("int_cast"),

    // reserve constexp for compiler time expansion of certain
    STATIC_STR("consteval"),

    // reserve cycle keywords
    STATIC_STR("for"),
    STATIC_STR("while"),
    STATIC_STR("do"),

};


constexpr size_t reserved_words_count = sizeof(reserved_words) / sizeof(STRING);



#endif


