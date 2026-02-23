


#include <stdio.h>
#include <stdlib.h>

#include "c_block/token.h"
#include "c_block/file/allocator_definition.h"
#include "c_block/file/struct/struct_operations.h"
#include "c_block/string/struct_operations.h"

bool file_allocator__initialised = false;

struct FILE_ALLOC__ file_allocator;


static bool find_file_on_allocator(const STRING _fname, FILE_ID* file_id) {
    if (file_allocator._len == 0) return false;

    for (size_t i = 0; i < file_allocator._len; ++i) {
        if (compare_strings(&file_allocator._files[i]._f_name, &_fname) == false)
            continue;

        *file_id = i;
        return true;
    }

    return false;
}



static LOG_SIGNAL alloc_reserve(const size_t _size) {
    if (file_allocator._buff > _size && _size != 0) return OK;

    const size_t recv_buffer = file_allocator._buff;

    if (file_allocator._buff == 0) file_allocator._buff = 1;
    while (file_allocator._buff < _size) file_allocator._buff <<= 1;

    FILE_STRUCT* new_file_alloc = realloc(file_allocator._files, sizeof(FILE_STRUCT) * file_allocator._buff);

    if (new_file_alloc == nullptr) {
        file_allocator._buff = recv_buffer;
        return ERR_MEM;
    }


    TOKEN_STREAM* new_tkn_strm_alloc = realloc(file_allocator._files, sizeof(TOKEN_STREAM) * file_allocator._buff);

    if (new_file_alloc == nullptr) {
        file_allocator._buff = recv_buffer;
        return ERR_MEM;
    }

    file_allocator._files = new_file_alloc;
    file_allocator._tkn_streams = new_tkn_strm_alloc;

    return OK;

}



FILE_ID process_file(const STRING* _file_name) {
    FILE_ID file_id = 0;
    if (find_file_on_allocator(*_file_name, &file_id) == true) return file_id;

 // add file to allocator:

    file_id = file_allocator._len;

    if (alloc_reserve(file_allocator._len + 1) != OK) {
        printf("Unrecoverable reallocation, can't continue with compilation (check if you did not run out of RAM or something :/)");
        abort();
    }

    auto file_struct = EMPTY_FILE_STRUCT;
    if (read_file(&file_struct, _file_name) != OK) {
        printf("Couldn't open file: %s", _file_name->_str);
        abort();
    }

    const auto token_stream = tokenisator_automata(&file_struct, file_id);

    file_allocator._files[file_id] = file_struct;
    file_allocator._tkn_streams[file_id] = token_stream;

    ++file_allocator._len;

    return file_id;
}



FILE_STRUCT get_file_struct(const FILE_ID _file_id) {
    return file_allocator._files[_file_id];
}


void initialise_file_allocator() {
    if (file_allocator__initialised == true) return;

    file_allocator__initialised = true;

    file_allocator._len = 0;
    file_allocator._buff = 0;
    file_allocator._files = nullptr;
    file_allocator._tkn_streams = nullptr;

}


TOKEN_STREAM get_token_stream(const FILE_ID _file_id) {
    return file_allocator._tkn_streams[_file_id];
}
