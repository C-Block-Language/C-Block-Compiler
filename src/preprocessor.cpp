
#include "preprocessor.h"

#include "parser/parser.h"

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


        if (attempt_directive(token_on_line, line, i) == true) continue;
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
                if (current_token->line() != line) {
                    --index;
                    return nullptr;
                }
                found_token = true;
                break;
            default:
                --index;
                return nullptr;
        }
    }
    return current_token;
}

bool c_preprocessor::attempt_directive(const size_t token_on_line, size_t line, size_t &index) {

    if (token_on_line != 0)                                 return false;

    auto hashtag_token = token_stream->at(index);
    if (hashtag_token->type() != SINGLE_CHAR)               return false;
    if (hashtag_token->content() != "#")                    return false;

    const auto directive_token = get_next_token(index);

    /// TODO: add a logger & handler for malformed preprocessor linebreaking
    if (directive_token == nullptr) return false;

    if (directive_token->line() != hashtag_token->line())   return false;
    if (directive_token->content() == "set")                return set_property(index);
    if (directive_token->content() == "define")             return define_macro(index);
    if (directive_token->content() == "include")            return include_file(index);
    if (directive_token->content() == "undef")              return undefine_macro(index);

    /// TODO: add a logger & handler to indicate a non-existent preprocessor directive
    return false;

}
