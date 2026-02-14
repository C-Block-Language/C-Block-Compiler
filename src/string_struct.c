


#include "string_struct.h"

#include <stdlib.h>
#include <string.h>




constexpr size_t CHR_PER_SIZE_T = sizeof(size_t) / sizeof(char);



STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str) {
    if (_target_struct->_str == nullptr) {
        _target_struct->_len = 0;
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
    free(_target_struct->_str);
    _target_struct->_str = nullptr;
    _target_struct->_len = 0;
    _target_struct->_buff = 1;
}




size_t string_len(const STRING* target) {
    return target->_len;
}




void erase_string(STRING* _target_struct) {
    _target_struct->_len = 0;
    _target_struct->_str[0] = '\0';
}



STR_LOG str_reserve(STRING* _target_struct, const size_t size) {
    if (_target_struct->_buff > size) return OK;

    const size_t recv_buffer = _target_struct->_buff;
    while (_target_struct->_buff < size + 1) _target_struct->_buff <<= 1;

    char* new_ptr = realloc(_target_struct->str, _target_struct->_buff);

    if (new_ptr == nullptr) {
        _target_struct->_buff = recv_buffer;
        return ERR_MEM;
    }

    _target_struct->str = new_ptr;
    return OK;
}



void str_pop_back(STRING* _target_struct, const size_t N) {
    if (N > _target_struct->_len) {
        erase_string(_target_struct);
        return;
    }
    _target_struct->_len -= N;
    _target_struct->_str[_target_struct->_len + 1] = '\0';
}

STR_LOG append_str(STRING *_target_struct, const char *_str) {
    const size_t len = strlen(_str);
    if (str_reserve(_target_struct, _target_struct->length + len) == ERR_MEM) return ERR_MEM;

    (void) memcpy(_target_struct->_str + _target_struct->_len, _str, len + 1);
    _target_struct->_len += len;
    return OK;
}


STR_LOG compare_string(const STRING* _struct1, const STRING* _struct2) {
    if (_struct1->length != _struct2->length) return DIFF;

    const char* str1 = _struct1->str;
    const char* str2 = _struct2->str;

    const size_t str_byte_len = _struct1->length * sizeof(char);
    const size_t len_in_blocks = str_byte_len / sizeof(size_t);

    size_t block1 = 0;  size_t block2 = 0;
    for (size_t i = 0; i < len_in_blocks; ++i) {
        memcpy(&block1, &str1[i * CHR_PER_SIZE_T], sizeof(size_t));     // I suppose a faster way to do string comparison
        memcpy(&block2, &str2[i * CHR_PER_SIZE_T], sizeof(size_t));

        if (block1 != block2) return DIFF;
    }


    const size_t alrdy_comp_chars = len_in_blocks * CHR_PER_SIZE_T;
    const size_t leftover_bytes = str_byte_len - alrdy_comp_chars;

    size_t leftover_str1 = 0;
    size_t leftover_str2 = 0;

    (void)memcpy(&leftover_str1, &str1[alrdy_comp_chars], leftover_bytes);
    (void)memcpy(&leftover_str2, &str2[alrdy_comp_chars], leftover_bytes);

    if (leftover_str1 != leftover_str2) return DIFF;


    return OK;
}


