




#include <stdio.h>


#include "c_block/file/struct/struct_operations.h"

#include <assert.h>

#include "c_block/string.h"
#include "c_block/file/sys_ops.h"



inline void file_to_str_struct(FILE* _file, STRING* _target_struct) {
    fseek(_file, 0, SEEK_SET);

    while (!feof(_file)) {
        char page[FILE_STRING_PAGE_SIZE + 1] = {};

        int c = 0;
        size_t iter = 0;
        do {
            c = fgetc(_file);
            if (c == EOF) break;
            page[iter] = (char) c;
            ++iter;
        } while (iter < FILE_STRING_PAGE_SIZE);

        page[iter] = '\0';
        append_str(_target_struct, page);

    }
}



LOG_SIGNAL read_file(FILE_STRUCT* _target_file, const STRING* _f_name) {
    assert(_f_name->_str != nullptr);                                               // Can't operate over empty strings.
    assert(
        _target_file->_f_name._str == nullptr && _target_file->_f_content._str == nullptr
    );                                                                              // Can't read onto non-empty file
                                                                                    // structs.

    const auto file_name = get_absolute_path(_f_name);

    if (file_name._str == NULL) return FERR_OPEN;

    const auto file_ptr = fopen(file_name._str, "r");

    if (file_ptr == nullptr) return FERR_OPEN;

    auto file_str = EMPTY_STR;
    file_to_str_struct(file_ptr, &file_str);

    _target_file->_f_content = file_str;
    _target_file->_f_name = file_name;

    fclose(file_ptr);

    return OK;
}









