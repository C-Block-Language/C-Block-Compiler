

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_H
#define C_BLOCK_COMPILER_STRING_STRUCT_H

#include <stddef.h>

 * @brief A fail-safe pointer to iterate in & out of a string struct.
 */
typedef struct {
    STRING* _str_struct;
    size_t _index;
    size_t _line;
    size_t _column;
} STR_PTR;



/**
 * @brief An initialiser macro helper for a null string pointer.
 */
#define NULL_STR_PTR (STR_PTR){._str_struct = nullptr, ._index = 0, ._line = 1, ._column = 1}




/**
 * @brief Assigns the start index of a string struct.
 * @param [in] _target_ptr string pointer to be assigned.
 * @param [in] _str_struct string struct that will be assigned.
 */
void assg_str_ptr(STR_PTR* _target_ptr, STRING* _str_struct);




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
#define next_line(_target_ptr) {end_line(_target_ptr); (void) advance_char(_target_ptr);}




/**
 * @brief Moves a string pointer to the start of the previous line.
 * @param _target_ptr pointer to the string pointer to be operated.
 */
#define previous_line(_target_ptr) {carriage_return(_target_ptr); (void) recoil_char(_target_ptr); carriage_return(_target_ptr);}


#endif
