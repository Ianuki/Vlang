#ifndef PARSER_H
#define PARSER_H

typedef enum {
    NODE_DECL,
    NODE_MACRO,
    NODE_ASSIGN,
    NODE_NUMBER,
    NODE_IDENTIFIER,
    NODE_BINARY_OP
} NodeType;

typedef struct ASTNode {
    NodeType type;
    union {
        struct { const char* name; int value; } macro;
        struct { const char* name; struct ASTNode* expr; } decl;
        struct { const char* name; struct ASTNode* expr; } assign;
        int number;
        const char* identifier;
        struct { struct ASTNode* left; struct ASTNode* right; char op; } binary;
    };
} ASTNode;

#endif