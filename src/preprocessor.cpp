
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

token* c_preprocessor::get_next_token(size_t &index) {

    size_t line = token_stream->at(index)->line();

    token* current_token = nullptr;

    bool found_token = false;
    while (found_token == false) {
        ++index;
        current_token = token_stream->at(index);
        switch (current_token->type()) {
            case SINGLE_CHAR:
                if (current_token->content() == "\\") { ++line; continue; }
            case SHY_IDENTIFIER:
            case LOUD_IDENTIFIER:
            case LITERAL:
                if (current_token->line() != line) return nullptr;
                found_token = true;
                break;
            default:
                return nullptr;
        }
    }
    return current_token;
}
