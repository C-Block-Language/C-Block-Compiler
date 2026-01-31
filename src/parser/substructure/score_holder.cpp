
#include "../syntax_structure.h"
#include "../../token.h"

using namespace C_BLOCK;






bool syntax_structure::attempt_score_holder() {
    const stream_backtrack original_position = stream->get_position();

    const auto score_holder = new syntax_structure(*stream);
    if (score_holder->attempt(SELECTOR) == true) {
        syntax = OBJECTIVE_ID;
        substructure_list.push_back(score_holder);
        return true;
    }
    delete score_holder;




    vector<token*> token_buffer;

    bool continue_looping = true;
    while (continue_looping) {
        stream_backtrack last_pos = stream->get_position();

        token_buffer.push_back(new token(*stream));
        const auto current_token = token_buffer.back();

        if (token_buffer.size() == 1 || current_token->content() == "*") {
            break;
        }

        switch (current_token->type()) {
            case LITERAL:
            case SHY_IDENTIFIER:
            case LOUD_IDENTIFIER:
            case NUMBER:
                break;

            case DOUBLE_QUOTED_STRING:
                continue_looping = false;
                if (!has_linebreaks(*current_token)) break;
            case SINGLE_QUOTED_STRING:
                continue_looping = false;
                if (!has_spaces(*current_token)) break;

            case SINGLE_CHAR_SYMBOL:
                if (current_token->content() == "+") break;
                if (current_token->content() == "-") break;
                if (current_token->content() == ".") break;

            default:
                continue_looping = false;
                delete current_token;
                token_buffer.pop_back();
                stream->set_position(last_pos);
        }
    }

    if (token_buffer.empty() == true) {
        stream->set_position(original_position);
        return false;
    };

    token_list.append_range(token_buffer);
    syntax = OBJECTIVE_ID;
    return true;
}




