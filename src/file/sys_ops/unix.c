


#include <stdlib.h>

#include "c_block/file/sys_ops.h"
#include "c_block/string/struct_operations.h"


STRING get_absolute_path(const STRING* _fname_str) {
    // If you see this not compiling, means that you're probably on Windows! Compile the
    // target named 'win32_build' instead or compile directly in a Unix like system (like Linux).
    // Or.... have fun your date with CMake & crosscompiling!
    //                                                                      -- CosmicAxolotl, 2026.
    char* str = realpath(_fname_str->_str, nullptr);

    auto str_struct = EMPTY_STR;
    char_arrt_struct(&str_struct, str);
    free(str);

    return str_struct;

}


