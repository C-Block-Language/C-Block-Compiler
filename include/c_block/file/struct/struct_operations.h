


#ifndef C_BLOCK_COMPILER_FILE_STRUCT_OPERATIONS_H
#define C_BLOCK_COMPILER_FILE_STRUCT_OPERATIONS_H

#include "c_block/file/struct/definition.h"
#include "c_block/log_signal.h"


/**
 * @brief Opens a file & buffers it into a file struct
 * @param _target_file pointer to the file struct to be written on.
 * @param _f_name name of the relative path field of the file.
 * @returns OK if successful, an FERR signal otherwise.
 */
LOG_SIGNAL read_file(FILE_STRUCT* _target_file, STRING* _f_name);



#endif




