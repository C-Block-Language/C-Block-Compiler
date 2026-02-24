

#ifndef C_BLOCK_COMPILER_TOKEN_PTR_OPS_H
#define C_BLOCK_COMPILER_TOKEN_PTR_OPS_H


#include "ptr_definition.h"


/**
 * @brief Assigns the start index of a string struct.
 * @param [in] _target_ptr string pointer to be assigned.
 * @param [in] _tkn_strm string struct that will be assigned.
 */
void assg_tkn_ptr(TKN_STREAM_PTR* _target_ptr, TOKEN_STREAM* _tkn_strm);




/**
 * @brief Returns the token where the string pointer is at.
 * @param [in] _target_ptr string pointer to get character from.
 * @note If the pointer is at the end of the stream, it will return an EMPTY TOKEN.
 */
TOKEN gtkn(const TKN_STREAM_PTR *_target_ptr);




/**
 * @brief Advances one character on a string pointer.
 * @param [in] _target_ptr string pointer to operate on.
 * @returns the character advanced.
 * @note If it reaches end of string, it will return an EMPTY TOKEN not advance more.
 */
TOKEN advance_tkn(TKN_STREAM_PTR* _target_ptr);




/**
 * @brief Moves back one character on a string pointer.
 * @param [in] _target_ptr token stream pointer to operate on.
 * @returns the token where the pointer is at after moving back.
 * @note If the start index is reached, the pointer will stall on the start index.
 */
TOKEN recoil_tkn(TKN_STREAM_PTR* _target_ptr);




#endif


