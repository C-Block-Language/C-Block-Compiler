
#ifndef C_BLOCK_COMPILER_TOKEN_H
#define C_BLOCK_COMPILER_TOKEN_H



#include "token/struct.h"
#include "token/stream.h"


/**
 * @brief A finite state machine that takes a file string & returns its token stream.
 * @param _file file struct to be tokenised
 * @returns a token stream that contains all legal tokens.
 */
TOKEN_STREAM tokenisator_automata(FILE_STRUCT* _file);



#endif