


#include "string_struct.h"

STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str) {
    if (_target_struct->str == nullptr) {
        _target_struct->length = 0;
        _target_struct->buffer = 1;
    }

    const size_t recv_length = _target_struct->length;


    _target_struct->length = strlen(_str);
    if (str_reserve(_target_struct, _target_struct->length) == ERR_MEM) {
        _target_struct->length = recv_length;
        return ERR_MEM;
    }

    (void)memcpy(_target_struct->str, _str, sizeof(char) * (_target_struct->length + 1));
    return OK;
}



void free_string(STRING* _target_struct) {
    free(_target_struct->str);
    _target_struct->str = nullptr;
    _target_struct->length = 0;
    _target_struct->buffer = 1;
}



size_t string_len(const STRING* target) {
    return target->length;
}



void erase_string(STRING* _target_struct) {
    _target_struct->length = 0;
    _target_struct->str[0] = '\0';
}



STR_LOG str_reserve(STRING* _target_struct, const size_t size) {
    if (_target_struct->buffer >= size) return OK;

    const size_t recv_buffer = _target_struct->buffer;
    while (_target_struct->buffer < size) _target_struct->buffer <<= 1;

    char* new_ptr = realloc(_target_struct->str, _target_struct->buffer);

    if (new_ptr == nullptr) {
        _target_struct->buffer = recv_buffer;
        return ERR_MEM;
    }

    _target_struct->str = new_ptr;
    return OK;
}
