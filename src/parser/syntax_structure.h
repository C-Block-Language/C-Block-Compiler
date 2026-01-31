
#ifndef C_BLOCK_COMPILER_PARSE_CHECK_H
#define C_BLOCK_COMPILER_PARSE_CHECK_H

#include <vector>

#include "../c_stream.h"
#include "../token.h"

inline bool has_linebreaks(C_BLOCK::token &token) {
    const size_t size = token.content().size() - 2;
    for (size_t i = 1; i < size; ++i) {
        if (token.content()[i] == '\n') return true;
    }
    return false;
}

inline bool has_spaces(C_BLOCK::token &token) {
    const size_t size = token.content().size() - 2;
    for (size_t i = 1; i < size; ++i) {
        if (token.content()[i] == ' ') return true;
    }
    return false;
}


namespace C_BLOCK {

    enum syntax_structure_type {
        /// Initial structure while opening a file
        ROOT,

        /// [shy_identifier || LOUD_IDENTIFIER || Literal]
        /// or single or doubled-quoted string without spaces
        WEAK_STRING_WITHOUT_SPACES,

        /// #include "double-quoted string without \n symbols"
        INCLUDE_DIRECTIVE,

        SET_DIRECTIVE,

        /// LOUD_IDENTIFIER::LOUD_IDENTIFIER/.../LOUD_NESTING(<command signature>) {}
        COMMAND_DEFINITION,

        /// [auto|int|float|resource_location|position|bool|compound] Literal, [...]
        COMMAND_SIGNATURE,

        /// shy_identifier::shy_identifier/.../shy_identifier(<function signature>)
        FUNCTION_DEFINITION,

        /// [int|void] Literal, [...]
        FUNCTION_SIGNATURE,

        /// [some valid subinstruction];
        INSTRUCTION,

        /// valid NBT path
        NBT_PATH,

        /// weak string without spaces<valid objective id>
        SCORE_HOLDER,

        /// valid_score_holder<valid_objective_name>
        SCORE_SOURCE,

        NBT_SOURCE,

        /// valid scoreboard objective
        OBJECTIVE_ID,

        /// valid selector
        SELECTOR
    };


    class syntax_structure {
    public:
        /// attempts to tokenise the stream & check if it's valid C-Block syntax
        explicit syntax_structure(c_stream &stream);
        ~syntax_structure();


        /// attempts to fill the syntax structure following the TYPE grammar
        bool attempt(syntax_structure_type type);
        vector<token*> tokens();

    private:
        token read_token();
        bool attempt_objective_id();
        bool attempt_score_holder();
        bool attempt_score_source();

        c_stream* stream;
        syntax_structure_type syntax = ROOT;
        vector<token*> token_list;
        vector<syntax_structure*> substructure_list;
    };


}

#endif //C_BLOCK_COMPILER_PARSE_CHECK_H