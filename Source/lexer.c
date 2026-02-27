#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "Includes/lexer.h"

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
    {"@label", TOKEN_LABEL},
};

#define KEYWORD_COUNT (sizeof(keywords) / sizeof(Keyword))

static int is_at_end(Lexer* lexer) { return *lexer->current == '\0'; }
static char advance(Lexer* lexer) { lexer->current++; return lexer->current[-1]; }
static char peek(Lexer* lexer) { return *lexer->current; }
static char peek_next(Lexer* lexer) { if (is_at_end(lexer)) return '\0'; return lexer->current[1]; }

static int match(Lexer* lexer, char expected) {
    if (is_at_end(lexer)) return 0;
    if (*lexer->current != expected) return 0;
    lexer->current++;
    return 1;
}

static Token make_token(Lexer* lexer, TokenType type) {
    Token token;
    token.type = type;
    token.start = lexer->start;
    token.length = (int)(lexer->current - lexer->start);
    token.value = 0;
    return token;
}

static void skip_whitespace(Lexer* lexer) {
    while (1) {
        char c = peek(lexer);

        if (c == ' ' || c == '\t' || c == '\r') {
            advance(lexer);
        }
        else if (c == '/' && peek_next(lexer) == '*') {
            advance(lexer); advance(lexer);

            while (!(peek(lexer) == '*' && peek_next(lexer) == '/')) {
                if (is_at_end(lexer)) return;
                advance(lexer);
            }

            advance(lexer); advance(lexer);
        }
        else {
            break;
        }
    }
}

static Token make_number(Lexer* lexer) {
    while (isdigit(peek(lexer)))
        advance(lexer);

    Token token = make_token(lexer, TOKEN_NUMBER);
    token.value = strtol(token.start, NULL, 10);
    return token;
}

static Token check_keyword(Lexer* lexer) {
    while (isalnum(peek(lexer)) || peek(lexer) == '_') advance(lexer);

    uint64_t length = (uint64_t)(lexer->current - lexer->start);

    for (int i = 0; i < KEYWORD_COUNT; i++) {
        if (strlen(keywords[i].name) == length && strncmp(lexer->start, keywords[i].name, length) == 0) {
            return make_token(lexer, keywords[i].type);
        }
    }

    return make_token(lexer, TOKEN_IDENTIFIER);
}

void vl_lexer_init(Lexer* lexer, const char* source) {
    lexer->start = source;
    lexer->current = source;
    lexer->line = 0;
}

Token vl_lexer_next(Lexer* lexer) {
    skip_whitespace(lexer);

    lexer->start = lexer->current;

    if (is_at_end(lexer))
        return make_token(lexer, TOKEN_EOF);

    char c = advance(lexer);

    if (isalpha(c) || c == '_' || c == '@')
        return check_keyword(lexer);

    if (isdigit(c))
        return make_number(lexer);

    switch (c) {
        case '\n': return make_token(lexer, TOKEN_EOL);
        case ';':  return make_token(lexer, TOKEN_EOL);

        case '+': return make_token(lexer, TOKEN_PLUS);
        case '-': return make_token(lexer, TOKEN_MINUS);
        case '*': return make_token(lexer, TOKEN_STAR);
        case '/': return make_token(lexer, TOKEN_SLASH);

        case '=':
            if (match(lexer, '=')) return make_token(lexer, TOKEN_EQEQ);
            return make_token(lexer, TOKEN_EQ);

        case ',': return make_token(lexer, TOKEN_COMMA);
        case ':': return make_token(lexer, TOKEN_COLON);
        case '(': return make_token(lexer, TOKEN_LPAREN);
        case ')': return make_token(lexer, TOKEN_RPAREN);
        case '[': return make_token(lexer, TOKEN_LBRACKET);
        case ']': return make_token(lexer, TOKEN_RBRACKET);
    }

    return make_token(lexer, TOKEN_EOF);
}
