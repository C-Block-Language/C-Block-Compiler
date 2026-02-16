

#ifndef C_BLOCK_COMPILER_TOKEN_FMS_H
#define C_BLOCK_COMPILER_TOKEN_FMS_H

#include "struct/definition.h"


/**
 * @brief The FSM's state to check for a reserved word token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `RESERVED_WORD` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN reserved_word_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a shy identifier token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `SHY_IDENTIFIER` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN shy_identifier_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a shy identifier token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `SHY_IDENTIFIER` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN loud_identifier_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a literal token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `LITERAL` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN literal_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a single char token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `SINGLE_CHAR` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN single_char_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for an open bracket token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `BRACKET_OPEN` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN bracket_open_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a close bracket token.
 * @param _spos string pointer that points to the start of the possible
 * @returns a valid `BRACKET_CLOSE` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN bracket_close_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a single quoted string token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `SINGLE_QUOTED_STRING` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN single_quoted_string_state(STR_PTR* _spos);

/**
 * @brief The FSM's state to check for a single quoted string token.
 * @param _spos string pointer that points to the start of the possible token.
 * @returns a valid `SINGLE_QUOTED_STRING` token if successful, an `INVALID_STATE` token otherwise.
 * @note If it fails, it does not modify the _cpos pointer. Otherwise, it moves it to the end of the read token.
 */
static TOKEN double_quoted_string_state(STR_PTR* _spos);

/**
 * @brief Parses & checks if an escaping sequence is valid number.
 * @param _spos string pointer that points to the character escape sequence.
 * @returns `true` if successful escaping is done, `false` otherwise.
 * @note It will always advance the string pointer at least one character.
 */
static TOKEN number_state(STR_PTR* _spos);


/**
 * @brief Assistant function to the FSM to skip whitespaces & comments.
 * @param _spos string pointer of the FSM's current position on the file string.
 */
static void skip_comments_n_whitespaces(STR_PTR* _spos);

/**
 * @brief Assistant function to the FSM states. Used when returning a token.
 * @param type type to label the built token.
 * @param s_pos string pointer that points to the start of the token.
 * @param e_pos string pointer that points to the end of the token
 * @returns a token will the specified content.
 */
static TOKEN return_tkn(TKN_TYPE type, STR_PTR* s_pos, STR_PTR e_pos);

/**
 * @brief Parses & checks if an escaping sequence is valid under SNBT specs.
 * @param _spos string pointer that points to the character escape sequence.
 * @returns `true` if successful escaping is done, `false` otherwise.
 * @note It will always advance the string pointer at least one character.
 */
static bool process_escaping_sequence(STR_PTR* _spos);



#endif


