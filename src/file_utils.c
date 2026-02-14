


#include "file_utils.h"

#include <assert.h>


void jump_n_skip(STR_PTR* _target_ptr, const size_t _args_count, ...) {
    va_list ap;

    char buffer[_args_count + 1];

    va_start(ap, _args_count);

    for (size_t i = 0; i < _args_count; ++i) {
        buffer[i] = (char) va_arg(ap, int);
        assert(buffer[i] != '\0');          /* Can't ignore the null terminator */
    }

    va_end(ap);

    buffer[_args_count] = '\0';

    char c = 0;

    do {
        c = advance_char(_target_ptr);
        bool matches = false;
        for (size_t i = 0; i < _args_count; ++i) {
            if (c == buffer[i]) matches = true;
        }
        if (matches == true) continue;
        (void) recoil_char(_target_ptr);
        return;
    } while (c != '\0');

}


void file_to_str_struct(FILE* _file, STRING* _target_struct) {
    fseek(_file, 0, SEEK_SET);

    while (!feof(_file)) {
        char page[PAGE_SIZE + 1] = {};

        int c = 0;
        size_t iter = 0;
        do {
            c = fgetc(_file);
            if (c == EOF) break;
            page[iter] = (char) c;
            ++iter;
        } while (iter < PAGE_SIZE);

        page[iter] = '\0';
        append_str(_target_struct, page);

    }
}


