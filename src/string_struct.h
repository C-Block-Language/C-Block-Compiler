

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_H
#define C_BLOCK_COMPILER_STRING_STRUCT_H

#include <stddef.h>

typedef struct {
    char *str;
    size_t length;
    size_t buffer;
} STRING;

typedef enum {
    /// Good to continue.
    OK,

    /// Error, can't continue.
    ERR,

    /// memory allocation error
    ERR_MEM,

    /// Strings are not equal.
    DIFF
} STR_LOG;

/**
 * @brief Converts a primitive char array (null-terminated) into a string struct.
 * @param [in] _target_struct string struct to be affected.
 * @param [in] _str primitive array of characters to append.
 * @returns `OK` if successful, an ERR signal otherwise.
 */
STR_LOG char_arrt_struct(STRING* _target_struct, const char* _str);
/**
* @brief Frees the content of a string struct.
* @param [in] _target_struct string struct to be deleted.
*/
void free_string(STRING* _target_struct);
#endif
