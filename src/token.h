
#ifndef C_BLOCK_COMPILER_TOKEN_H
#define C_BLOCK_COMPILER_TOKEN_H
#include "c_stream.h"
#include <cstdint>
#include <string>

#define MAX_BUFFER_SIZE 2048

using namespace std;

namespace C_BLOCK {

    static constexpr size_t double_char_symbol_count = 15;
    static string double_char_symbols[double_char_symbol_count] = {
        // reserve the 4 basic arithmetic-assign operations + switch operator
        // (IDK why anyone would that last one this anyway, lol)
        "+=",
        "-=",
        "*=",
        "/=",
        "%=",
        "><",

        // reserve comparisons
        ">=",
        "<=",
        "==",
        "!=",

        // reserve the ++ & -- operators;
        "++",
        "--",

        // reserve the store/modify operator
        "<-",

        // reserve logic operators
        "&&",
        "||"
    };

    static constexpr size_t reserved_word_count = 28;
    static string reserved_words[reserved_word_count] = {
        // Reserve all modifier execute sub-commands
        "execute",
        "if",
        "align",
        "anchored",
        "as",
        "at",
        "facing",
        "in",
        "on",
        "positioned",
        "rotated",
        "summon",
        "run",

        // reserve return keyword
        "return",

        // reserve native command keyword
        "native",
        // return function return types
        "void",
        "int",

        // reserve NBT path sources
        "nbt_path",
        "entity",
        "storage",
        "block",

        // reserve score variable type
        "score",

        // reserve nbt operations
        "append",
        "insert",
        "merge",
        "prepend",
        "set",
        "remove"
    };


    enum token_type {
        WIP,
        RESERVED_WORD,
        SHY_IDENTIFIER,
        LOUD_IDENTIFIER,
        LITERAL,
        SINGLE_CHAR_SYMBOL,
        DOUBLE_CHAR_SYMBOL,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        SINGLE_QUOTED_STRING,
        DOUBLE_QUOTED_STRING,
        NUMBER,
        MISCELLANEOUS,
    };

    class token {
    public:
        explicit token(c_stream &file);
        [[nodiscard]] token_type type() const;
        string content();
        [[nodiscard]] size_t column() const;
        [[nodiscard]] size_t line() const;

    private:
        bool is_double_quoted_string(FILE* _file, fpos_t original_pos, c_stream &stream);
        bool is_single_quoted_string(FILE* _file, fpos_t original_pos);
        bool is_single_char_symbol(FILE* _file, fpos_t original_pos);
        bool is_double_char_symbol(FILE* _file, fpos_t original_pos);
        bool is_loud_identifier(FILE* _file, fpos_t original_pos);
        bool is_shy_identifier(FILE* _file, fpos_t original_pos);
        bool is_reserved_word(FILE* _file, fpos_t original_pos);
        bool is_bracket(FILE* _file, fpos_t original_pos);
        bool is_number(FILE* _file, fpos_t original_pos);
        bool is_literal(FILE* _file, fpos_t original_pos);

        token_type t_type;
        string token_str;
        /// pos[0] := line,  pos[1] := column
        size_t pos[2] = {0, 0};
    };
}

#endif