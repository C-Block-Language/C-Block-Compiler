

#ifndef C_BLOCK_COMPILER_STRING_POINTER_OPS_H
#define C_BLOCK_COMPILER_STRING_POINTER_OPS_H


#include "definition.h"
#include "../struct/definition.h"



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


