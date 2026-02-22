



#ifndef C_BLOCK_COMPILER_FILE_STRUCT_SYS_OPS_H
#define C_BLOCK_COMPILER_FILE_STRUCT_SYS_OPS_H


#include "c_block/string/struct_definition.h"


/**
 * @brief Creates
 * @param _fname_str pointer to a string struct that represents the name of the file name to convert into absolute path.
 * @returns A well formatted string struct if successfull, otherwise an empty string.
 */
STRING get_absolute_path(const STRING* _fname_str);





#endif


