
#include "c_stream.h"
#include <iostream>

using namespace C_BLOCK;


void c_stream::move_on_column(const size_t amount) {    pos[0] += amount;       }
void c_stream::move_on_line(const size_t amount) {      pos[1] += amount;       }
void c_stream::reset_line() {                           pos[0] = 1;             }
size_t c_stream::column() const {                       return pos[0];          }
FILE* c_stream::stream() const {                        return _file;           }
size_t c_stream::line() const {                         return pos[1];          }


c_stream::c_stream(const char* file) {
    _file = fopen(file, "r");
    pos[0] = 1; pos[1] = 1;
    if (_file != nullptr) return;
    printf("File \"%s\" couldn't be opened!", file);
}


void c_stream::berserk_along_whitespaces_and_comments() {

    char buffer[2] = {'\0','\0'};
    buffer[1] = static_cast<char>(getc(_file));

    if (buffer[1] != '/') goto whitespace;

    comment_start: /// valid comments are '//' & '/* */' kinds
    buffer[0] = buffer[1];
    buffer[1] = static_cast<char>(getc(_file));         ++pos[0];

    switch (buffer[1]) {
        case '/':
            goto short_comment;
        case '*':
            goto multiline_comment;
        default:
            ungetc(buffer[1], _file);                   --pos[0];
            fpos_t tmp_repos;
            fgetpos(_file, &tmp_repos);         // troll workaround for ungetc() limited guarantees xD
            fsetpos(_file, &tmp_repos);
            ungetc(buffer[0], _file);                   --pos[0];
            return;
    }

    short_comment:
    while (feof(_file) == 0) {
        buffer[0] = buffer[1];
        buffer[1] = static_cast<char>(getc(_file));     ++pos[0];
        if (buffer[1] == '\n') break;
    }                                                   ++pos[1]; pos[0] = 1;
    buffer[0] = buffer[1];
    buffer[1] = static_cast<char>(getc(_file));
    goto whitespace;



    multiline_comment:
    while (feof(_file) == 0) {
        buffer[0] = buffer[1];
        buffer[1] = static_cast<char>(getc(_file));     ++pos[0];
        if (buffer[1] == '\n')                        { ++pos[1]; pos[0] = 1; }
        if (buffer[1] == '*') continue;
        if (buffer[0] == '*' && buffer[1] == '/') break;
    }
    buffer[0] = buffer[1];
    buffer[1] = static_cast<char>(getc(_file));         ++pos[0];




    whitespace:
    while (feof(_file) == 0) {
        switch (buffer[1]) {
            case '\n':                                ++pos[1]; pos[0] = 1;
                buffer[0] = buffer[1];
                buffer[1] = static_cast<char>(getc(_file));
                continue;
            case '\t':
            case ' ':
                buffer[0] = buffer[1];
                buffer[1] = static_cast<char>(getc(_file));     ++pos[0];
                continue;
            default:
                break;
        }
        if (buffer[1] == '/') goto comment_start;

        ungetc(buffer[1], _file);
        return;
    }
}

stream_backtrack c_stream::get_position() const {
    stream_backtrack position_to_return;
    fgetpos(_file, &position_to_return.file_position);
    position_to_return.pos[0] = this->pos[0];
    position_to_return.pos[1] = this->pos[1];
    return position_to_return;
}

void c_stream::set_position(const stream_backtrack &position) {
    fsetpos(_file, &position.file_position);
    pos[0] = position.pos[0];
    pos[1] = position.pos[1];
}