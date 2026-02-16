
#ifndef C_BLOCK_COMPILER_TOKEN_H
#define C_BLOCK_COMPILER_TOKEN_H



#include "token/struct.h"
#include "token/stream.h"
#include "token/stream_pointer.h"


/**
 * @brief A finite state machine that takes a file string & returns its token stream.
 * @param _file_str file string to be tokenised
 * @returns a token stream that contains all legal tokens.
 */
TOKEN_STREAM tokenisator_fsm(STRING* _file_str);



#endif