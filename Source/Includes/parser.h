#ifndef PARSER_H
#define PARSER_H

#define CODE_BLOCK_STACK_SIZE 128

#include <stdint.h>

#include "lexer.h"

typedef enum {
    ARBITRARY, /* do -> end*/
    BLOCK_FUNCTION,
    BLOCK_IF,
    BLOCK_REPEAT
} CodeBlockType;

typedef struct {
    size_t id;
    CodeBlockType type;
} CodeBlock;

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

typedef struct {
    CodeBlock code_block_stack[CODE_BLOCK_STACK_SIZE];
    size_t block_id;
    uint8_t block_stack_pointer; /* uint8_t -> CODE_BLOCK_STACK_SIZE < 256 */
} Parser;

void vl_parser_init(Parser* parser);
void vl_parser_parse(Parser* parser, Lexer* lexer);

#endif

/*
    push var1: U64

    N* Push:
        N* Identifier = "var1"
        N* Type = DT_U64

*/