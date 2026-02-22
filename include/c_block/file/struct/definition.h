


#ifndef C_BLOCK_COMPILER_FILE_STRUCT_DEFINITION_H
#define C_BLOCK_COMPILER_FILE_STRUCT_DEFINITION_H

#include "c_block/string/struct_definition.h"

#define FILE_STRING_PAGE_SIZE 4096


typedef struct {
    /* absolute path to the file */     STRING* _f_name;
    /* string with the file content */  STRING* _f_content;
} FILE_STRUCT;

#define EMPTY_FILE_HANDLER (FILE_HANDLER) {_f_name = nullptr, _f_content = nullptr}

#endif


