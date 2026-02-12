


#include "string_struct.h"

STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str) {
    if (_target_struct->str == nullptr) {
        _target_struct->length = 0;
        _target_struct->_buff = 1;
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
    _target_struct->_buff = 1;
}



size_t string_len(const STRING* target) {
    return target->length;
}



void erase_string(STRING* _target_struct) {
    _target_struct->length = 0;
    _target_struct->str[0] = '\0';
}



STR_LOG str_reserve(STRING* _target_struct, const size_t size) {
    if (_target_struct->_buff > size) return OK;

    const size_t recv_buffer = _target_struct->_buff;
    while (_target_struct->_buff < size + 1) _target_struct->_buff <<= 1;

    char* new_ptr = realloc(_target_struct->str, _target_struct->buffer);

    if (new_ptr == nullptr) {
        _target_struct->_buff = recv_buffer;
        return ERR_MEM;
    }

    _target_struct->str = new_ptr;
    return OK;
}



void str_pop_back(STRING* _target_struct, const size_t N) {
    if (N > _target_struct->length) {
        erase_string(_target_struct);
        return;
    }
    _target_struct->length -= N;
    _target_struct->str[_target_struct->length + 1] = '\0';
}

STR_LOG append_str(STRING *_target_struct, const char *_str) {
    const size_t len = strlen(_str);
    if (str_reserve(_target_struct, _target_struct->length + len) == ERR_MEM) return ERR_MEM;

    (void)memcpy(_target_struct->str + _target_struct->length, _str, len + 1);
    _target_struct->length += len;
    return OK;
}
