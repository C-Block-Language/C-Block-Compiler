
#ifndef C_BLOCK_COMPILER_C_STREAM_H
#define C_BLOCK_COMPILER_C_STREAM_H

#include <cstdio>
#include <vector>

using namespace std;

namespace C_BLOCK {

    typedef struct {
        fpos_t file_position;
        size_t pos[2];
    } stream_backtrack;

    class c_stream {
    public:
        explicit c_stream(const char *file);

        void reset_line();
        void move_on_column(size_t amount);
        void move_on_line(size_t amount);
        void berserk_along_whitespaces_and_comments();

        [[nodiscard]] stream_backtrack get_position() const;
        void set_position(const stream_backtrack &position);

        [[nodiscard]] FILE* stream() const;

        [[nodiscard]] size_t column() const;
        [[nodiscard]] size_t line() const;

        void read_token();

    private:
        FILE* _file = nullptr;
        /// pos[1] := line,  pos[0] := column
        size_t pos[2];
    };
}

#endif