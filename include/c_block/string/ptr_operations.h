

#ifndef C_BLOCK_COMPILER_STRING_POINTER_OPS_H
#define C_BLOCK_COMPILER_STRING_POINTER_OPS_H

#include <stdint.h>
#include "c_block/string/ptr_definition.h"



/**
 * @brief Advances a string pointer over a string struct ignoring a set of single characters, will stop when met with a different character.
 * @param _target_ptr pointer to the file stream to advance on.
 * @param _args_count amount of characters listed as variable arguments (curse you, dookie C!)
 * @param ... set of characters to be ignored.
 */
void jump_n_skip(STR_PTR* _target_ptr, size_t _args_count, ...);




/**
 * @brief Advances a string pointer over a string struct ignoring all character till met with any of a set of specific characters.
 * @param _target_ptr pointer to the file stream to advance on.
 * @param _args_count amount of characters listed as variable arguments (curse you, dookie C!)
 * @param ... set of characters to seek.
 */
void jump_n_seek(STR_PTR* _target_ptr, size_t _args_count, ...);




/**
 * @brief Assigns the start index of a string struct.
 * @param [in] _target_ptr string pointer to be assigned.
 * @param [in] _str_struct string struct that will be assigned.
 */
void assg_str_ptr(STR_PTR* _target_ptr, STRING* _str_struct);




/**
 * @brief Returns the character where the string pointer is at.
 * @param [in] _target_ptr string pointer to get character from.
 */
char gchar(const STR_PTR *_target_ptr);




/**
 * @brief Advances one character on a string pointer.
 * @param [in] _target_ptr string pointer to operate on.
 * @returns the character advanced.
 * @note If it reaches end of string, it will return the null terminator & not advance more.
 */
char advance_char(STR_PTR* _target_ptr);




/**
 * @brief Moves back one character on a string pointer.
 * @param [in] _target_ptr string pointer to operate on.
 * @returns the character where the pointer is at after moving back.
 * @note If the start index is reached, the pointer will stall on the start index.
 */
char recoil_char(STR_PTR* _target_ptr);




/**
 * @brief Rolls back a string pointer to the start of the current line.
 * @param [in] _target_ptr string pointer to operate on.
 */
void carriage_return(STR_PTR* _target_ptr);




/**
 * @brief Jumps a string pointer to the end of the line.
 * @param [in] _target_ptr string pointer to operate on.
 * @note If the pointer is on the last line of the string, it will be moved to the end of the string.
 */
void end_line(STR_PTR *_target_ptr);




/**
 * @brief Moves a string pointer to the start of the next line.
 * @param _target_ptr pointer to the string pointer to be operated.
 */
static void next_line(STR_PTR* _target_ptr) {
    end_line(_target_ptr);
    (void) advance_char(_target_ptr);
}




/**
 * @brief Moves a string pointer to the start of the previous line.
 * @param _target_ptr pointer to the string pointer to be operated.
 */
static void previous_line(STR_PTR *_target_ptr) {
    carriage_return(_target_ptr);
    (void) recoil_char(_target_ptr);
    carriage_return(_target_ptr);
}




#endif


