
#include "token.h"


using namespace C_BLOCK;

token_type token::type()    const { return t_type;              }
string token::content()           { return token_str;           }
size_t token::column()      const { return pos[0];              }
size_t token::line()        const { return pos[1];              }




token::token(c_stream &file) {
    file.berserk_along_whitespaces_and_comments();
    pos[1] = file.line();
    pos[0] = file.column();
    t_type = WIP;

    FILE* _file = file.stream();

    fpos_t original_pos;
    fgetpos(_file, &original_pos);

    if (is_single_quoted_string(_file, original_pos))           goto passed;
    if (is_double_quoted_string(_file, original_pos, file))  return; // it already handles the file position (as it's multilined)
    if (is_single_char_symbol(_file, original_pos))             goto passed;
    if (is_double_char_symbol(_file, original_pos))             goto passed;
    if (is_bracket(_file, original_pos))                        goto passed;
    if (is_number(_file, original_pos))                         goto passed;
    if (is_reserved_word(_file, original_pos))                  goto passed;
    if (is_shy_identifier(_file, original_pos))                 goto passed;
    if (is_loud_identifier(_file, original_pos))                goto passed;
    if (is_literal(_file, original_pos))                        goto passed;
    return;

    passed:
    file.move_on_column(token_str.size());

}

inline bool matches_any_reserved_word(const char buffer_char, const size_t i) {
    for (size_t j = 0; j < reserved_word_count - 1; ++j) {
        if (i > reserved_words[j].size()) continue;
        if (buffer_char == reserved_words[j][i]) return true;
    }
    return false;
}

bool token::is_reserved_word(FILE* _file, const fpos_t original_pos) {
    char buffer[MAX_BUFFER_SIZE]; buffer[MAX_BUFFER_SIZE - 1] = '\0';

    size_t i = 0;
    bool possible_reserved_word = false;

    while (feof(_file) == 0 && i < MAX_BUFFER_SIZE) {
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            case ' ': case '\t': case '\n':
                ungetc(buffer[i], _file);
                buffer[i] = '\0';
                i = MAX_BUFFER_SIZE - 1;
                break;
            default:
                possible_reserved_word = matches_any_reserved_word(buffer[i], i);
        }
        if (possible_reserved_word == false) break;
        ++i;
    }


    if (possible_reserved_word == true) {
        const auto tmp_str = string(buffer);
        for (size_t j = 0; j < reserved_word_count; ++j) {
            if (tmp_str != reserved_words[j]) continue;
            token_str = reserved_words[j];
            t_type = RESERVED_WORD;
            return true;
        }
    }

    fsetpos(_file, &original_pos);
    return false;

}

bool token::is_shy_identifier(FILE* _file, const fpos_t original_pos) {
    char buffer[MAX_BUFFER_SIZE]; buffer[MAX_BUFFER_SIZE - 1] = '\0';
    size_t i = 0;

    bool possible_shy_identifier = true;

    while (feof(_file) == 0 && i < MAX_BUFFER_SIZE) {
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            case ' ': case '\t': case '\n':
                ungetc(buffer[i], _file);
                buffer[i] = '\0';
                i = MAX_BUFFER_SIZE - 1;
                break;

            default:
                if (!isalpha(buffer[i])) possible_shy_identifier = false;
                if (!islower(buffer[i])) possible_shy_identifier = false;
                if (buffer[i] == '_') possible_shy_identifier = true;
                if (isdigit(buffer[i]) && i > 0) possible_shy_identifier = true;
                break;

        }
        if (possible_shy_identifier == false) break;
        ++i;
    }

    if (possible_shy_identifier == true) {
        token_str = string(buffer);
        t_type = SHY_IDENTIFIER;
        return true;
    }

    fsetpos(_file, &original_pos);
    return false;

}

bool token::is_loud_identifier(FILE* _file, const fpos_t original_pos) {
    char buffer[MAX_BUFFER_SIZE]; buffer[MAX_BUFFER_SIZE - 1] = '\0';
    size_t i = 0;

    bool possible_loud_identifier = true;

    while (feof(_file) == 0 && i < MAX_BUFFER_SIZE) {
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            case ' ': case '\t': case '\n':
                ungetc(buffer[i], _file);
                buffer[i] = '\0';
                i = MAX_BUFFER_SIZE - 1;
                break;

            default:
                if (!isalpha(buffer[i])) possible_loud_identifier = false;
                if (!isupper(buffer[i])) possible_loud_identifier = false;
                if (buffer[i] == '_') possible_loud_identifier = true;
                if (isdigit(buffer[i]) && i > 0) possible_loud_identifier = true;
                break;

        }
        if (possible_loud_identifier == false) break;
        ++i;
    }

    if (possible_loud_identifier == true) {
        token_str = string(buffer);
        t_type = LOUD_IDENTIFIER;
        return true;
    }

    fsetpos(_file, &original_pos);
    return false;

}

bool token::is_double_quoted_string(FILE* _file, const fpos_t original_pos, c_stream &stream) {
    char buffer[MAX_BUFFER_SIZE]; buffer[MAX_BUFFER_SIZE - 1] = '\0';

    buffer[0] = static_cast<char>(getc(_file));
    if (buffer[0] != '\"') {
        fsetpos(_file, &original_pos);
        return false;
    }

    bool escaping = false;

    size_t i;
    for (i = 1; i < MAX_BUFFER_SIZE - 1 && feof(_file) == 0; ++i) {
        buffer[i] = static_cast<char>(getc(_file));
        stream.move_on_column(1);

        if (buffer[i] == '\\' && escaping == false) {
            escaping = true;
            continue;
        }
        if (escaping == true) {
            escaping = false;
            switch (buffer[i]) {
                case '\\':
                case '\"':
                    continue;
                default:
                    break;
            }
        }
        if (buffer[i] == '\n') {
            stream.reset_line();
            stream.move_on_line(1);
            continue;
        }
        if (buffer[i] == '\"') break;
    }

    buffer[i + 1] = '\0';
    token_str = string(buffer);
    t_type = SINGLE_QUOTED_STRING;
    return true;
}

bool token::is_bracket(FILE* _file, const fpos_t original_pos) {
    char buffer[2]; buffer[1] = '\0';
    buffer[0] = static_cast<char>(getc(_file));

    switch (buffer[0]) {
        case '[': case '{': case '(':
            t_type = BRACKET_OPEN;
            token_str = string(buffer);
            return true;
        case ']': case '}': case ')':
            t_type = BRACKET_CLOSE;
            token_str = string(buffer);
            return true;
        default:
            fsetpos(_file, &original_pos);
            return false;
    }

}

bool token::is_single_char_symbol(FILE* _file, fpos_t original_pos) {
    char buffer[2]; buffer[1] = '\0';
    buffer[0] = static_cast<char>(getc(_file));

    switch (buffer[0]) {
        case ':': case ';': case '.': case ',':             // colon, semicolon, dot & comma
        case '=': case '+': case '-': case '/': case '%':   // arithmetic operators
        case '@':                                           // for selectors & inline starters
        case '^': case '~':                                 // relative & local position symbols
        case '!':                                           // negation symbol
        case '<': case '>':                                 // basic comparisons
            t_type = SINGLE_CHAR_SYMBOL;
            token_str = string(buffer);
            return true;
        default:
            fsetpos(_file, &original_pos);
            return false;
    }

}

bool token::is_double_char_symbol(FILE *_file, fpos_t original_pos) {
    char buffer[3]; buffer[2] = '\0';
    buffer[0] = static_cast<char>(getc(_file));
    buffer[1] = static_cast<char>(getc(_file));

    for (uint8_t i = 0; i < double_char_symbol_count - 1 && feof(_file) == 0; ++i) {
        if (string(buffer) == double_char_symbols[i]) return true;
    }



    return true;


}


inline bool parse_unicode_shortcode(char* buffer, FILE* _file, size_t &i) {
    for (uint8_t j = 0; j < 2; ++j) {
        ++i;
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            default:
                return false;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                break;
        }
    }
    return true;

}

inline bool parse_unicode_code(char* buffer, FILE * _file, size_t &i) {
    for (uint8_t j = 0; j < 4; ++j) {
        ++i;
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            default:
                return false;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                break;
        }
    }
    return true;

}

inline bool parse_unicode_long_code(char* buffer, FILE * _file, size_t &i) {
    for (uint8_t j = 0; j < 8; ++j) {
        ++i;
        buffer[i] = static_cast<char>(getc(_file));
        switch (buffer[i]) {
            default:
                return false;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
            case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
                break;
        }
    }
    return true;

}

bool token::is_single_quoted_string(FILE * _file, const fpos_t original_pos) {
    char buffer[MAX_BUFFER_SIZE]; buffer[MAX_BUFFER_SIZE - 1] = '\0';

    buffer[0] = static_cast<char>(getc(_file));
    if (buffer[0] != '\'') {
        fsetpos(_file, &original_pos);
        return false;
    }

    bool escaping = false;

    size_t i;
    for (i = 1; i < MAX_BUFFER_SIZE - 1 && feof(_file) == 0; ++i) {
        buffer[i] = static_cast<char>(getc(_file));
        if (buffer[i] == '\\' && escaping == false) {
            escaping = true;
            continue;
        }
        if (escaping == true) {
            escaping = false;
            switch (buffer[i]) {
                case 'b': case 'f': case 'n': case 'r':
                case 's': case 't':
                case '\\': case '\'': case '\"':
                    continue;
                case 'x':
                    if (!parse_unicode_shortcode(buffer, _file, i)) break;
                    /// TODO: Add the logger to signalise broken escaping sequence \x
                    break;
                case 'u':
                    if (!parse_unicode_code(buffer, _file, i)) break;
                    /// TODO: Add the logger to signalise broken escaping sequence \u
                    break;
                case 'U':
                    if (!parse_unicode_long_code(buffer, _file, i)) break;
                    /// TODO: Add the logger to signalise broken escaping sequence \U
                    break;
                default:
                    /// TODO: Add the logger to signalise invalid escaping sequence error
                    break;
            }
        }

        switch (buffer[i]) {
            case '\n':
                /// TODO: Add the logger to signalise invalid linebreaks
                ungetc('\n', _file);
            case '\'':
                goto finish;
            default:
                break;
        }
    }

    finish:
    buffer[i + 1] = '\0';
    token_str = string(buffer);
    t_type = SINGLE_QUOTED_STRING;
    return true;
}



