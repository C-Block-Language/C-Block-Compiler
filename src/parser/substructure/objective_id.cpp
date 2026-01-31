
#include "../syntax_structure.h"
#include "../../token.h"

using namespace C_BLOCK;

bool syntax_structure::attempt_objective_id() {
    const stream_backtrack original_position = stream->get_position();

    vector<token*> token_buffer;

    bool continue_looping = true;
    while (continue_looping) {
        stream_backtrack last_pos = stream->get_position();

        token_buffer.push_back(new token(*stream));
        const auto current_token = token_buffer.back();

        if (token_buffer.size() == 1 || current_token->content() == "*") {
            continue_looping = false;
            break;
        }

        switch (current_token->type()) {
            case LITERAL:
            case SHY_IDENTIFIER:
            case LOUD_IDENTIFIER:
            case NUMBER:
                break;

            case SINGLE_CHAR_SYMBOL:
                if (current_token->content() == "+") break;
                if (current_token->content() == "-") break;

            default:
                continue_looping = false;
                delete current_token;
                token_buffer.pop_back();
                stream->set_position(last_pos);
        }
    }
}

