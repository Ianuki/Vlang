#ifndef PARSER_H
#define PARSER_H

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

#endif

/*
    push var1: U64

    N* Push:
        N* Identifier = "var1"
        N* Type = DT_U64

*/