
#ifndef C_BLOCK_COMPILER_TOKEN_H
#define C_BLOCK_COMPILER_TOKEN_H


#include "c_block/file/struct/definition.h"
#include "c_block/token/struct.h"
#include "c_block/token/stream.h"


/**
 * @brief A finite state machine that takes a file string & returns its token stream.
 * @param _file file struct to be tokenised
 * @param _id
 * @returns a token stream that contains all legal tokens.
 */
TOKEN_STREAM tokenisator_automata(FILE_STRUCT* _file, FILE_ID _id);



#endif