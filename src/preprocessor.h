

#ifndef C_BLOCK_COMPILER_PREPROCESSOR_H
#define C_BLOCK_COMPILER_PREPROCESSOR_H

#include <unordered_map>

#include "token.h"

namespace C_BLOCK {
    class c_preprocessor {
    public:
        token* get_next_token(size_t index);

        bool attempt_directive(size_t token_on_line, size_t line, size_t& index);

        explicit c_preprocessor(vector<token*>& og_tkn_stream);
    private:
        bool define_macro(size_t &index);
        bool undefine_macro(size_t &index);
        bool set_property(size_t &index);
        bool include_file(size_t &index);
        unordered_map<string, vector<token*>> macro_table;
        unordered_map<string, vector<token*>> property_table;
        vector<token*>* token_stream;
    };
}

#endif