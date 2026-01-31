
#include "syntax_structure.h"

using namespace C_BLOCK;

token syntax_structure::read_token() {

}

vector<token*> syntax_structure::tokens() {
    return token_list;
}

syntax_structure::syntax_structure(c_stream &stream) {
    this->stream = &stream;
}


bool syntax_structure::attempt(const syntax_structure_type type) {
    switch (type) {
        default:
        case ROOT:
            return false; // invalid case, ROOT is reserved upon creating a new structure, thus never attempted
        case WEAK_STRING_WITHOUT_SPACES:
        case INCLUDE_DIRECTIVE:
        case SET_DIRECTIVE:
        case COMMAND_DEFINITION:
        case COMMAND_SIGNATURE:
        case FUNCTION_DEFINITION:
        case FUNCTION_SIGNATURE:
        case INSTRUCTION:
        case NBT_PATH:
        case SCORE_HOLDER:
        case SELECTOR:
        case OBJECTIVE_ID:
            return attempt_objective_id();
    }
}
