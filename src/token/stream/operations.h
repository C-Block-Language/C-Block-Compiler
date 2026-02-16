

#ifndef C_BLOCK_COMPILER_TOKEN_STREAM_OPS_H
#define C_BLOCK_COMPILER_TOKEN_STREAM_OPS_H


#include "definition.h"
#include "../../log_signal.h"



/**
* @brief Reserves capacity on a token stream (to save memory reallocations).
* @param [in] _target_tkn_strm pointer to the token stream struct to be affected.
* @param [in] _size size in characters of token to at least reserve.
* @returns `OK` if successful, an ERR signal otherwise.
*/
LOG_SIGNAL tkn_stream_reserve(TOKEN_STREAM* _target_tkn_strm, size_t _size);




/**
 * @brief Appends a token to the end of a token stream.
 * @param _target_tkn_strm pointer to the token stream to be affected.
 * @param _tkn token to append the stream.
 * @return `OK` if successful, an ERR signal otherwise.
 */
LOG_SIGNAL appendt_tkn_stream(TOKEN_STREAM* _target_tkn_strm, TOKEN _tkn);




/**
 * @brief Executes an operation to every token of the stream.
 * @param _target_tkn_strm pointer to the token stream to be affected.
 * @param _tkn_op function pointer to a valid token operation.
 * @note Very useful to free a bunch of tokens automatically.
 */
void op_on_all_tkns(TOKEN_STREAM* _target_tkn_strm, void(*_tkn_op)(TOKEN*));




/**
 * @brief Frees all tokens of a token stream.
 * @param _target_tkn_strm pointer to the token stream to be affected.
 * @warning it will turn the token stream into an EMPTY_TOKEN_STREAM, but it WON'T free the tokens' content.
 * Do a respective call to `op_on_all_tkns` with the `free_token` function previous to calling this function to free all tokens.
 */
void free_tkn_stream(TOKEN_STREAM* _target_tkn_strm);




#endif


