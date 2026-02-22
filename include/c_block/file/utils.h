

#ifndef C_BLOCK_COMPILER_FILE_UTILS_H
#define C_BLOCK_COMPILER_FILE_UTILS_H


#include <stdio.h>
#include "c_block/string/struct_definition.h"

/**
 * @brief Writes all of a file content into a string struct.
 * @param _file file stream pointer to iterate over.
 * @param _target_struct string struct to save all file content.
 */
void file_to_str_struct(FILE* _file, STRING* _target_struct);




#endif