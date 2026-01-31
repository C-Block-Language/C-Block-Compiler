
#include "../syntax_structure.h"
#include "../../token.h"

using namespace C_BLOCK;


#define fail  { delete score_holder;                        \
delete objective;                           \
stream->set_position(original_position);    \
return false; }



bool syntax_structure::attempt_score_source() {
    const stream_backtrack original_position = stream->get_position();

    // alloc space for the score holder & objective substructures
    const auto score_holder = new syntax_structure(*stream);
    const auto objective = new syntax_structure(*stream);




    if (score_holder->attempt(SCORE_HOLDER) == false)       fail;



    auto opening_bracket = token(*stream);
    switch (opening_bracket.type()) {
        case SINGLE_QUOTED_STRING:
            if (opening_bracket.content() == "<")           break;
        default:                                            fail;
    }



    if (objective->attempt(OBJECTIVE_ID) == false)          fail;



    auto closing_bracket = token(*stream);
    switch (opening_bracket.type()) {
        case SINGLE_QUOTED_STRING:
            if (opening_bracket.content() == ">") break;
        default:
            fail;
    }

    substructure_list.reserve(2);
    substructure_list.push_back(score_holder);
    substructure_list.push_back(objective);

    return true;

}

#undef fail
