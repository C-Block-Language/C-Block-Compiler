


#ifndef C_BLOCK_COMPILER_FILE_ALLOCATOR_DEFINITION_H
#define C_BLOCK_COMPILER_FILE_ALLOCATOR_DEFINITION_H





#include "c_block/token/stream/struct_definition.h"
#include "c_block/file/struct/definition.h"


extern bool file_allocator__initialised;

extern struct FILE_ALLOC__ {
    FILE_STRUCT* _files;
    TOKEN_STREAM* _tkn_streams;
    size_t _buff;
    size_t _len;
} file_allocator;


#define NULL_FILE (FILE_ID) 0



#endif


