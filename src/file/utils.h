

#ifndef C_BLOCK_COMPILER_FILE_UTILS_H
#define C_BLOCK_COMPILER_FILE_UTILS_H


#include <stdio.h>
#include "../string_struct.h"

#define PAGE_SIZE 4096

/**
 * @brief Writes all of a file content into a string struct.
 * @param _file file stream pointer to iterate over.
 * @param _target_struct string struct to save all file content.
 */
void file_to_str_struct(FILE* _file, STRING* _target_struct);


/**
 * @brief Advances in a file stream ignoring a set of single characters, will stop when met with a different character.
 * @param _target_ptr pointer to the file stream to advance on.
 * @param _args_count amount of characters listed as variable arguments (curse you, dookie C!)
 * @param ... set of characters to be ignored.
 */
void jump_n_skip(STR_PTR* _target_ptr, size_t _args_count, ...);



/**
 * @brief Advances in a file stream ignoring all character till met with any of a set of specific characters.
 * @param _target_ptr pointer to the file stream to advance on.
 * @param _args_count amount of characters listed as variable arguments (curse you, dookie C!)
 * @param ... set of characters to seek.
 */
void jump_n_seek(STR_PTR* _target_ptr, size_t _args_count, ...);


#endif