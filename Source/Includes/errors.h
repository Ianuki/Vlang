#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
    ERR_NO_ERROR, // For the sake of using 0 as the default no error exit value
    ERR_SCOPE_OVERFLOW,
    ERR_SCOPE_UNDERFLOW,
    ERR_EXPECTED_GOT,
    ERR_SEEK_FOUND_EOF,
    ERR_UNCLOSED_STRING,
    ERR_INVALID_SYNTAX
} ErrorCodes;

#endif