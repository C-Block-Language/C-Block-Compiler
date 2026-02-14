

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_H
#define C_BLOCK_COMPILER_STRING_STRUCT_H

#include <stddef.h>




typedef struct {
    char* _str;
    size_t _len;
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
 * @brief A fail-safe pointer to iterate in & out of a string struct.
 */
typedef struct {
    STRING* _str_struct;
    size_t _index;
    size_t _line;
    size_t _column;
} STR_PTR;


/**
 * @brief An initialiser macro helper for an empty string struct.
 */
#define EMPTY_STR (STRING){._str = nullptr, ._buff = 1, ._len = 0}

/**
 * @brief An initialiser macro helper for a null string pointer.
 */
#define NULL_STR_PTR (STR_PTR){._str_struct = nullptr, ._index = 0, ._line = 1, ._column = 1}




/**
 * @brief Assigns the start index of a string struct.
 * @param [in] _target_ptr string pointer to be assigned.
 * @param [in] _str_struct string struct that will be assigned.
 */
void assg_str_ptr(STR_PTR* _target_ptr, STRING* _str_struct);
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
STR_LOG compare_strings(const STRING* _struct1, const STRING* _struct2);





#endif
