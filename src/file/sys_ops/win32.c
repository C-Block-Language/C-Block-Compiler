



#include <stdlib.h>

#include "c_block/file/sys_ops.h"
#include "c_block/string.h"






STRING get_absolute_path(const STRING* _fname_str) {
    // If you see this not compiling, means that you're probably on a Unix-like system! Compile the
    // target named 'unix_build' instead or compile directly on Windows. Or.... have fun your date
    // with CMake & crosscompiling!
    //                                                                      -- CosmicAxolotl, 2026.
    char* str = _fullpath(nullptr, _fname_str->_str, _fname_str->_len + 1);

    auto str_struct = EMPTY_STR;
    char_arrt_struct(&str_struct, str);
    free(str);


    auto str_ptr = NULL_STR_PTR;

    assg_str_ptr(&str_ptr, &str_struct);

    while (true) {
        jump_n_seek(&str_ptr, 1, '\\');

        if (gchar(&str_ptr) == '\0') break;
        str_ptr._str_struct->_str[str_ptr._index] = '/';            // unreadable garbage that I did not care to wrap
                                                                    // on a function (so far), means to replace a
                                                                    // character to where the pointer is currently,
                                                                    // TD;DR: Bill Gates & Co. ruining my life as usual.
    }

    return str_struct;
}



