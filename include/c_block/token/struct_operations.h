

#ifndef C_BLOCK_COMPILER_TOKEN_STRUCT_OPS_H
#define C_BLOCK_COMPILER_TOKEN_STRUCT_OPS_H


#include "c_block/token/struct_definition.h"




/**
* @brief Frees the content of a token struct.
* @param [in] _target_tkn string struct to be deleted.
*/
void free_token(TOKEN* _target_tkn);




/**
 * @brief Returns the type of token.
 * @param _target_tkn pointer to the token to access its type.
 * @returns the type of the token.
 */
TKN_TYPE tkn_type(const TOKEN* _target_tkn);


void debug_token_print(TOKEN* _target_tkn);

#endif


