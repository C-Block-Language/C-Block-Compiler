

#ifndef C_BLOCK_COMPILER_LOG_SIGNAL_H
#define C_BLOCK_COMPILER_LOG_SIGNAL_H


typedef enum {
    /// Good to continue.
    OK,

    /// Error, can't continue.
    ERR,

    /// memory allocation error
    ERR_MEM,

    /// Strings are not equal.
    STR_DIFF,

    /// Couldn't open file
    FERR_OPEN
} LOG_SIGNAL;

#endif


