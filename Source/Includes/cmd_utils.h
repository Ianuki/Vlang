#ifndef CMD_UTILS_H
#define CMD_UTILS_H

#include "lexer.h"

const char* tk_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF:
            return "TOKEN_EOF";
        case TOKEN_EOL:
            return "TOKEN_EOL";
        case TOKEN_IDENTIFIER:
            return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER:
            return "TOKEN_NUMBER";
        case TOKEN_PUSH:
            return "TOKEN_PUSH";
        case TOKEN_SET:
            return "TOKEN_SET";
        case TOKEN_REPEAT:
            return "TOKEN_REPEAT";
        case TOKEN_END:
            return "TOKEN_END";
        case TOKEN_JUMPIF:
            return "TOKEN_JUMPIF";
        case TOKEN_BREAKIF:
            return "TOKEN_BREAKIF";
        case TOKEN_FN:
            return "TOKEN_FN";
        case TOKEN_ENDFN:
            return "TOKEN_ENDFN";
        case TOKEN_ASM:
            return "TOKEN_ASM";
        case TOKEN_MACRO:
            return "TOKEN_MACRO";
        case TOKEN_LABEL:
            return "TOKEN_LABEL";
        case TOKEN_PLUS:
            return "TOKEN_PLUS";
        case TOKEN_MINUS:
            return "TOKEN_MINUS";
        case TOKEN_STAR:
            return "TOKEN_STAR";
        case TOKEN_SLASH:
            return "TOKEN_SLASH";
        case TOKEN_EQ:
            return "TOKEN_EQ";
        case TOKEN_EQEQ:
            return "TOKEN_EQEQ";
        case TOKEN_COMMA:
            return "TOKEN_COMMA";
        case TOKEN_COLON:
            return "TOKEN_COLON";
        case TOKEN_LPAREN:
            return "TOKEN_LPAREN";
        case TOKEN_RPAREN:
            return "TOKEN_RPAREN";
        case TOKEN_LBRACKET:
            return "TOKEN_LBRACKET";
        case TOKEN_RBRACKET:
            return "TOKEN_RBRACKET";
    }
}

#endif /* CMD_UTILS_H */
