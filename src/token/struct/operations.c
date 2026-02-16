

#include "operations.h"
#include "../../string/struct/operations.h"


void free_token(TOKEN* _target_tkn) {
    free_string(&_target_tkn->_str);
    _target_tkn->_type = INVALID_STATE;
    _target_tkn->_fpos = NULL_STR_PTR;
}
