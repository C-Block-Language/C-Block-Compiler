

#ifndef C_BLOCK_COMPILER_STRING_STRUCT_OPS_H
#define C_BLOCK_COMPILER_STRING_STRUCT_OPS_H


#include <stddef.h>

#include "c_block/string/ptr_definition.h"
#include "c_block/string/struct_definition.h"
#include "c_block/log_signal.h"




/**
 * @brief Converts a primitive char array (null-terminated) into a string struct.
 * @param [in] _target_struct string struct to be affected.
 * @param [in] _str primitive array of characters to append.
 * @returns `OK` if successful, an ERR signal otherwise.
 */
LOG_SIGNAL char_arrt_struct(STRING* _target_struct, const char* _str);




/**
 * @brief Takes two string pointers & converts the string within the two into a string struct.
 * @param _target_struct string struct to be affected.
 * @param _start string pointer to the start of the string.
 * @param _end string pointer to the end of the string.
 * @returns `OK` if successful, an ERR signal otherwise.
 */
LOG_SIGNAL str_ptrt_struct(STRING* _target_struct, const STR_PTR* _start, const STR_PTR* _end);




/**
* @brief Frees the content of a string struct.
* @param [in] _target_struct string struct to be deleted.
*/
void free_string(STRING* _target_struct);




/**
* @brief Returns the string size from a string struct.
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
* @brief Reserves capacity on a string struct (to save memory reallocations).
* @param [in] _target_struct pointer to the string struct to be affected.
* @param [in] _size size in characters of characters to at least reserve + 1 for the null terminator.
* @returns `OK` if successful, an ERR signal otherwise.
*/
LOG_SIGNAL str_reserve(STRING* _target_struct, size_t _size);




/**
* @brief Deletes N characters from the back of a string struct.
* @tparam STRING* target
* @param [in] _target_struct pointer to the string struct to be affected.
* @param [in] _n amount of characters to erase from the back.
*/
void str_pop_back(STRING* _target_struct, size_t _n);




/**
 * @brief Appends the contents from a primitive char array (null-terminated) to a string struct.
 * @param _target_struct pointer to string struct to be appended.
 * @param _str primitive char array to append into the string struc.
 * @returns `OK` if successful, an ERR otherwise.
 */
LOG_SIGNAL append_str(STRING* _target_struct, const char* _str);




/**
* @brief Compares two string structs.
* @param _struct1 pointer to first string struct to compare with.
* @param _struct2 pointer to second string struct to compare with.
* @returns `OK` if the strings are equal, `STR_DIFF` otherwise.
*/
LOG_SIGNAL compare_strings(const STRING* _struct1, const STRING* _struct2);




#endif


