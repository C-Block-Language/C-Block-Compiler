


#include "string_struct.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
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
