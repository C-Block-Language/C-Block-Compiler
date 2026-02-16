
#include "operations.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>


constexpr size_t CHR_PER_SIZE_T = sizeof(size_t) / sizeof(char);




LOG_SIGNAL char_arrt_struct(STRING* _target_struct, const char* _str) {
    if (_target_struct->_str == nullptr) {
        _target_struct->_len = 0;
        _target_struct->_buff = 1;
    }

    const size_t len = strlen(_str);
    if (str_reserve(_target_struct, len + 1) == ERR_MEM) return ERR_MEM;

    _target_struct->_len = len;
    (void) memcpy(_target_struct->_str, _str, sizeof(char) * (_target_struct->_len + 1));
    return OK;
}




LOG_SIGNAL str_ptrt_struct(STRING* _target_struct, const STR_PTR* _start, const STR_PTR* _end) {
    assert(_target_struct != nullptr);                  /* Can't operate on the null pointer.           */
    assert(_start != nullptr);                          /* Can't be null pointer.                       */
    assert(_end != nullptr);                            /* Can't be null pointer.                       */
    assert(_start->_str_struct != nullptr);             /* The start string pointer must not be null.   */
    assert(_end->_str_struct != nullptr);               /* The ending string pointer must not be null.  */
    assert(_start->_str_struct == _end->_str_struct);   /* The pointers must be over the same struct.   */
    assert(_start->_index < _end->_index);              /* The pointers must be on the correct sense.   */

    const size_t start_index = _start->_index;
    const size_t end_index = _end->_index;

    const size_t len = end_index - start_index;
    if (str_reserve(_target_struct, len) == ERR_MEM) return ERR_MEM;

    _target_struct->_len = len;
    (void) memcpy(_target_struct->_str, &_start->_str_struct->_str[start_index], sizeof(char) * len);

    _target_struct->_str[len] = '\0';
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




LOG_SIGNAL str_reserve(STRING* _target_struct, const size_t _size) {
    if (_target_struct->_buff > _size && _size != 0) return OK;

    const size_t recv_buffer = _target_struct->_buff;
    while (_target_struct->_buff < _size + 1) _target_struct->_buff <<= 1;


    char* new_ptr = realloc(_target_struct->_str, sizeof(char) * _target_struct->_buff);

    if (new_ptr == nullptr) {
        _target_struct->_buff = recv_buffer;
        return ERR_MEM;
    }

    _target_struct->_str = new_ptr;

    if (_target_struct->_len == 0) _target_struct->_str[0] = '\0';

    return OK;
}




void str_pop_back(STRING* _target_struct, const size_t _n) {
    if (_n > _target_struct->_len) {
        erase_string(_target_struct);
        return;
    }
    _target_struct->_len -= _n;
    _target_struct->_str[_target_struct->_len + 1] = '\0';
}




LOG_SIGNAL append_str(STRING *_target_struct, const char *_str) {
    const size_t len = strlen(_str);
    if (str_reserve(_target_struct, _target_struct->_len + len) == ERR_MEM) return ERR_MEM;
    if (len == 0) return OK;

    (void) memcpy(_target_struct->_str + _target_struct->_len, _str, len + 1);
    _target_struct->_len += len;
    return OK;
}




LOG_SIGNAL compare_strings(const STRING* _struct1, const STRING* _struct2) {
    if (_struct1->_len != _struct2->_len) return STR_DIFF;

    const char* str1 = _struct1->_str;
    const char* str2 = _struct2->_str;

    const size_t str_byte_len = _struct1->_len * sizeof(char);
    const size_t len_in_blocks = str_byte_len / sizeof(size_t);

    size_t block1 = 0;  size_t block2 = 0;
    for (size_t i = 0; i < len_in_blocks; ++i) {
        (void) memcpy(&block1, &str1[i * CHR_PER_SIZE_T], sizeof(size_t));     // I suppose a faster way to do string comparison
        (void) memcpy(&block2, &str2[i * CHR_PER_SIZE_T], sizeof(size_t));

        if (block1 != block2) return STR_DIFF;
    }


    const size_t alrdy_comp_chars = len_in_blocks * CHR_PER_SIZE_T;
    const size_t leftover_bytes = str_byte_len - alrdy_comp_chars;

    if (leftover_bytes == 0) return OK;

    size_t leftover_str1 = 0;
    size_t leftover_str2 = 0;

    (void) memcpy(&leftover_str1, &str1[alrdy_comp_chars], leftover_bytes);
    (void) memcpy(&leftover_str2, &str2[alrdy_comp_chars], leftover_bytes);

    if (leftover_str1 != leftover_str2) return STR_DIFF;

    return OK;
}



