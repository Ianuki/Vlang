#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    NODE_PUSH,
    NODE_SET,
    NODE_ASSIGN,
    NODE_IDENTIFIER,
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct { Token identifier; Token type; } push;
    };
} ASTNode;

void vl_parser_parse(Lexer* lexer);

#endif

/*
    push var1: U64

    N* Push:
        N* Identifier = "var1"
        N* Type = DT_U64

*/