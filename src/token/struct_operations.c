

#include "c_block/token/struct_operations.h"
#include "c_block/string/struct_operations.h"

#include <stdio.h>


void free_token(TOKEN* _target_tkn) {
    free_string(&_target_tkn->_str);
    _target_tkn->_type = INVALID_STATE;
    _target_tkn->_fpos = NULL_STR_PTR;
}




TKN_TYPE tkn_type(const TOKEN* _target_tkn) {
    return _target_tkn->_type;
}


void debug_token_print(/* const */ TOKEN* _target_tkn) {
    const auto str = _target_tkn->_str._str;
    const auto type = _target_tkn->_type;
    const auto fpos_line = _target_tkn->_fpos._line;
    const auto fpos_column = _target_tkn->_fpos._column;

    char* type_s = nullptr;
    switch (type) {
        case INVALID_STATE:
            type_s = "INVALID_STATE";
            break;
        case RESERVED_WORD:
            type_s = "RESERVED_WORD";
            break;
        case SHY_IDENTIFIER:
            type_s = "SHY_IDENTIFIER";
            break;
        case LOUD_IDENTIFIER:
            type_s = "LOUD_IDENTIFIER";
            break;
        case LITERAL:
            type_s = "LITERAL";
            break;
        case SINGLE_CHAR:
            type_s = "SINGLE_CHAR";
            break;
        case BRACKET_OPEN:
            type_s = "BRACKET_OPEN";
            break;
        case BRACKET_CLOSE:
            type_s = "BRACKET_CLOSE";
            break;
        case SINGLE_QUOTED_STRING:
            type_s = "SINGLE_QUOTED_STRING";
            break;
        case DOUBLE_QUOTED_STRING:
            type_s = "DOUBLE_QUOTED_STRING";
            break;
        case NUMBER:
            type_s = "NUMBER";
            break;
    }

    printf("{ token_type: %s, pos_in_file: %zu::%zu, content:\n%s}\n\n", type_s,fpos_line,fpos_column,str);

}


