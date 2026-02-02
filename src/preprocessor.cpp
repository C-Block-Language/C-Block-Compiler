
#include "preprocessor.h"

using namespace C_BLOCK;
c_preprocessor::c_preprocessor(vector<token *> &og_tkn_stream) {
    this->token_stream = &og_tkn_stream;


    size_t line = 0;
    size_t token_on_line = 0;
    for (size_t i = 0; i < token_stream->size(); ++i) {
        auto current_token = token_stream->at(i);


        if (current_token->line() > line) {
            ++line;
            token_on_line = 0;
        }
        ++token_on_line;


    }
}
