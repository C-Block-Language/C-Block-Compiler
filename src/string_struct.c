


#include "string_struct.h"

STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str) {
    if (_target_struct->str == nullptr) {
        _target_struct->length = 0;
        _target_struct->buffer = 1;
    }

    const size_t recv_length = _target_struct->length;


    _target_struct->length = strlen(_str);
    if (reserve_capacity(_target_struct, _target_struct->length) == ERR_MEM) {
        _target_struct->length = recv_length;
        return ERR_MEM;
    }

    (void)memcpy(_target_struct->str, _str, sizeof(char) * (_target_struct->length + 1));
    return OK;
}
