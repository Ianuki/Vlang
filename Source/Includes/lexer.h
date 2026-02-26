#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>

typedef enum {
    TOKEN_EOF,
    TOKEN_EOL,

    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,

    TOKEN_PUSH,
    TOKEN_SET,
    TOKEN_REPEAT,
    TOKEN_END,
    TOKEN_JUMPIF,
    TOKEN_BREAKIF,
    TOKEN_FN,
    TOKEN_ENDFN,
    TOKEN_ASM,
    TOKEN_MACRO,
    TOKEN_LABEL,

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_EQ,
    TOKEN_EQEQ,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET
} TokenType;

typedef struct {
    TokenType type;
    const char* start;
    uint64_t length;
    uint64_t value;
} Token;

typedef struct {
    const char* name;
    TokenType type;
} Keyword;

Keyword keywords[] = {
    {"push", TOKEN_PUSH},
    {"set", TOKEN_SET},
    {"repeat", TOKEN_REPEAT},
    {"end", TOKEN_END},
    {"jumpif", TOKEN_JUMPIF},
    {"breakif", TOKEN_BREAKIF},
    {"fn", TOKEN_FN},
    {"endfn", TOKEN_ENDFN},
    {"asm", TOKEN_ASM},
    {"@macro", TOKEN_MACRO},
    {"@label", TOKEN_MACRO},
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(Keyword))

typedef struct {
    const char* start;
    const char* current;
    uint64_t line;
} Lexer;

void vl_lexer_init(Lexer* lexer, const char* source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 0;
}

Token vl_lexer_next(Lexer*);

#endif /* LEXER_H */