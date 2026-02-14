


#include "string_struct.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>




constexpr size_t CHR_PER_SIZE_T = sizeof(size_t) / sizeof(char);




void assg_str_ptr(STR_PTR *_target_ptr, STRING *_str_struct) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_str_struct != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_target_ptr->_str_struct == nullptr);    /* Can't operate on non-null string pointers.   */

    _target_ptr->_str_struct = _str_struct;
    _target_ptr->_index = 0;
    _target_ptr->_line = 1;
    _target_ptr->_column = 1;
}




char advance_char(STR_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_target_ptr->_str_struct != nullptr);    /* Can't operate on null string pointers.       */

    const size_t string_max_index = string_len(_target_ptr->_str_struct) - 1;
    const size_t index = _target_ptr->_index;

    if (index > string_max_index) return '\0';

    const char c = _target_ptr->_str_struct->_str[index];

    if (c == '\n') {
        _target_ptr->_line += 1;
        _target_ptr->_column = 0;
    }

    _target_ptr->_index += 1;
    _target_ptr->_column += 1;

    return c;

}




char recoil_char(STR_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_target_ptr->_str_struct != nullptr);    /* Can't operate on non-null string pointers.   */


    const auto str = _target_ptr->_str_struct->_str;    // pointers to avoid a '->' hell
    const auto index = &_target_ptr->_index;
    const auto column = &_target_ptr->_column;

    if (*index == 0) return str[0];

    --*index;
    --*column;

    const char c = str[*index];                         // same here xd
    if (c != '\n') return c;
    if (*index == 0) return c;

    size_t catch_column = 1;
    size_t tmp_index = *index - 1;
    while (str[tmp_index] != '\n' && tmp_index > 0) {
        ++catch_column;
        --tmp_index;
    }

    *column = catch_column;
    --_target_ptr->_line;
    return '\n';

}




void carriage_return(STR_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_target_ptr->_str_struct != nullptr);    /* Can't operate on non-null string pointers.   */

    while (recoil_char(_target_ptr) != '\n' && _target_ptr->_index > 0) {}
    (void) advance_char(_target_ptr);
}



void end_line(STR_PTR *_target_ptr) {
    assert(_target_ptr != nullptr);                 /* Can't operate on the null pointer.           */
    assert(_target_ptr->_str_struct != nullptr);    /* Can't operate on non-null string pointers.   */

    char c;

    do c = advance_char(_target_ptr);
    while (c != '\n' && c != '\0');

    if (c == '\n') return (void) recoil_char(_target_ptr);
    (void) advance_char(_target_ptr);
}




STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str) {
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



STR_LOG str_ptrt_struct(STRING* _target_struct, const STR_PTR* _start, const STR_PTR* _end) {
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
    if (str_reserve(_target_struct, len + 1) == ERR_MEM) return ERR_MEM;

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




STR_LOG str_reserve(STRING* _target_struct, const size_t size) {
    if (_target_struct->_buff > size && size != 0) return OK;

    const size_t recv_buffer = _target_struct->_buff;
    while (_target_struct->_buff < size + 1) _target_struct->_buff <<= 1;

    char* new_ptr = realloc(_target_struct->_str, sizeof(char) * _target_struct->_buff);


    if (new_ptr == nullptr) {
        _target_struct->_buff = recv_buffer;
        return ERR_MEM;
    }




    _target_struct->_str = new_ptr;

    if (_target_struct->_len == 0) _target_struct->_str[0] = '\0';

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
    if (str_reserve(_target_struct, _target_struct->_len + len) == ERR_MEM) return ERR_MEM;
    if (len == 0) return OK;

    (void) memcpy(_target_struct->_str + _target_struct->_len, _str, len + 1);
    _target_struct->_len += len;
    return OK;
}




STR_LOG compare_strings(const STRING* _struct1, const STRING* _struct2) {
    if (_struct1->_len != _struct2->_len) return DIFF;

    const char* str1 = _struct1->_str;
    const char* str2 = _struct2->_str;

    const size_t str_byte_len = _struct1->_len * sizeof(char);
    const size_t len_in_blocks = str_byte_len / sizeof(size_t);

    size_t block1 = 0;  size_t block2 = 0;
    for (size_t i = 0; i < len_in_blocks; ++i) {
        (void) memcpy(&block1, &str1[i * CHR_PER_SIZE_T], sizeof(size_t));     // I suppose a faster way to do string comparison
        (void) memcpy(&block2, &str2[i * CHR_PER_SIZE_T], sizeof(size_t));

        if (block1 != block2) return DIFF;
    }


    const size_t alrdy_comp_chars = len_in_blocks * CHR_PER_SIZE_T;
    const size_t leftover_bytes = str_byte_len - alrdy_comp_chars;

    if (leftover_bytes == 0) return OK;

    size_t leftover_str1 = 0;
    size_t leftover_str2 = 0;

    (void) memcpy(&leftover_str1, &str1[alrdy_comp_chars], leftover_bytes);
    (void) memcpy(&leftover_str2, &str2[alrdy_comp_chars], leftover_bytes);

    if (leftover_str1 != leftover_str2) return DIFF;

    return OK;
}


