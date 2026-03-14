#ifndef UTILITIES_H
#define UTILITIES_H

#include "lexer.h"

static const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_EOF: return "TOKEN_EOF";
        case TOKEN_EOL: return "TOKEN_EOL";
        case TOKEN_IDENTIFIER: return "TOKEN_IDENTIFIER";
        case TOKEN_NUMBER: return "TOKEN_NUMBER";
        case TOKEN_PUSH: return "TOKEN_PUSH";
        case TOKEN_SET: return "TOKEN_SET";
        case TOKEN_REPEAT: return "TOKEN_REPEAT";
        case TOKEN_STRING: return "TOKEN_STRING";
        case TOKEN_JUMP: return "TOKEN_JUMP";
        case TOKEN_BREAK: return "TOKEN_BREAK";
        case TOKEN_FUNCTION: return "TOKEN_FUNCTION";
        case TOKEN_END: return "TOKEN_END";
        case TOKEN_IF: return "TOKEN_IF";
        case TOKEN_ASM: return "TOKEN_ASM";
        case TOKEN_IMPORT: return "TOKEN_IMPORT";
        case TOKEN_PLUS: return "TOKEN_PLUS";
        case TOKEN_MINUS: return "TOKEN_MINUS";
        case TOKEN_STAR: return "TOKEN_STAR";
        case TOKEN_SLASH: return "TOKEN_SLASH";
        case TOKEN_EQ: return "TOKEN_EQ";
        case TOKEN_EQEQ: return "TOKEN_EQEQ";
        case TOKEN_NEQ: return "TOKEN_NEQ";
        case TOKEN_COMMA: return "TOKEN_COMMA";
        case TOKEN_COLON: return "TOKEN_COLON";
        case TOKEN_LPAREN: return "TOKEN_LPAREN";
        case TOKEN_RPAREN: return "TOKEN_RPAREN";
        case TOKEN_LBRACKET: return "TOKEN_LBRACKET";
        case TOKEN_RBRACKET: return "TOKEN_RBRACKET";
        case TOKEN_EXCL: return "TOKEN_EXCL";
        default: return "TOKEN_UNKNOWN";
    }
}

static void mem_println(int length, const char* buffer) {
    printf("%.*s\n", length, buffer);
}

static void token_println(Token token) {
    printf("%.*s\n", (int)token.length, token.start);
}

#endif