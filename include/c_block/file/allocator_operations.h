


#ifndef C_BLOCK_COMPILER_FILE_ALLOCATOR_OPERATIONS_H
#define C_BLOCK_COMPILER_FILE_ALLOCATOR_OPERATIONS_H


#include "c_block/file/allocator_definition.h"


/**
 * @brief Processes a certain file into a token stream & adds it to the processed files if it wasn't already processed
 * (this so no extra tokenisation is required).
 * @param _file_name string struct with the file name of the
 * @returns the file ID of the processed file
 */
FILE_ID process_file(const STRING* _file_name);




/**
 * @brief Retrieves the token stream from a processed file.
 * @param _file_id File ID to get token stream from.
 * @returns The token stream linked to the file ID.
 */
TOKEN_STREAM get_token_stream(FILE_ID _file_id);




/**
 * @brief Retrieves the file struct from a file ID
 * @param _file_id file ID to retrieve.
 * @return the file struct associated to the file ID.
 */
FILE_STRUCT get_file_struct(FILE_ID _file_id);




/**
 * @brief Initialises the file allocator struct.
 */
void initialise_file_allocator();




#endif


