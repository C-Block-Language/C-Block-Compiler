

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_H
#define C_BLOCK_COMPILER_STRING_STRUCT_H

#include <stddef.h>

typedef struct {
    char* str;
    size_t length;
    size_t _buff;
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




/**
* @brief Returns string size from a string struct.
* @param [in] target pointer to the string struct to access its length.
* @returns string length as `size_t` data type.
*/
size_t string_len(const STRING* target);




/**
 * @brief Erases the content (without freeing memory) of a string struct
 * @param [in] _target_struct pointer to the string struct to be affected.
 */
void erase_string(STRING* _target_struct);




/**
* @brief Reserves capacity of a string struct (to save memory reallocations).
* @tparam STRING* target
* @param [in] _target_struct pointer to the string struct to be affected.
* @param [in] size size in characters of characters to at least reserve.
* @returns `OK` if successful, an ERR signal otherwise.
*/
STR_LOG str_reserve(STRING* _target_struct, size_t size);




/**
* @brief Deletes N characters from the back of a string struct.
* @tparam STRING* target
* @param [in] _target_struct pointer to the string struct to be affected.
* @param [in] N amount of characters to erase from the back.
*/
void str_pop_back(STRING* _target_struct, size_t N);




/**
 * @brief Appends the contents from a primitive char array (null-terminated) to a string struct.
 * @param _target_struct pointer to string struct to be appended.
 * @param _str primitive char array to append into the string struc.
 * @returns `OK` if successful, an ERR otherwise.
 */
STR_LOG append_str(STRING* _target_struct, const char* _str);




/**
* @brief Compares two string structs.
* @param _struct1 pointer to first string struct to compare with.
* @param _struct2 pointer to second string struct to compare with.
* @returns `OK` if the strings are equal, `DIFF` otherwise.
*/
STR_LOG compare_string(const STRING* _struct1, const STRING* _struct2);




#endif
