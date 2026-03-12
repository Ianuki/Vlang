/*

    Working on this
    Im gonna finish parsing everything then i'll generate an actual AST
    Printing it first instead of generating the AST makes debugging natural

*/

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>

#include "Includes/lexer.h"
#include "Includes/parser.h"
#include "Includes/utilities.h"

static void expect_token(Lexer* lexer, TokenType type) {
    Token token = vl_lexer_next(lexer);
    
    if (token.type != type) {
        printf("Parser error: expected '%s', got '%s'.\n", token_type_to_string(type), token_type_to_string(token.type));
        
        exit(1);
    }
}

static void enter_code_block(Parser* parser, CodeBlockType type) {
    if (parser->block_stack_pointer == CODE_BLOCK_STACK_SIZE) { /* Fix conflicts later (This check is absurdly idiotic) */
        printf("Parser error: code block overflow.");
        exit(1);
    }

    parser->code_block_stack[parser->block_stack_pointer++] = (CodeBlock){
        parser->block_id++,
        type
    };
}

static void leave_code_block(Parser* parser) {
    if (parser->block_stack_pointer == 0) { /* Same stupid check, Fix later */
        printf("Parser error: code block underflow.");
        exit(1);
    }

    parser->block_stack_pointer--;
}

static void parse_push(Lexer* lexer) {
    Token identifier = vl_lexer_next(lexer);
    expect_token(lexer, TOKEN_COLON);
    Token type = vl_lexer_next(lexer);
    
    printf("Push:\n");
    printf("----[ Name: ");
    for (int i = 0; i < identifier.length; i++) printf("%c", identifier.start[i]);
    printf("\n");
    
    printf("----[ Type: ");
    for (int i = 0; i < type.length; i++) printf("%c", type.start[i]);
    printf("\n");
}

static void parse_set(Lexer* lexer) {
    Token variable = vl_lexer_next(lexer);
    expect_token(lexer, TOKEN_EQ);
    Token value = vl_lexer_next(lexer);

    printf("Set:\n");
    printf("----[ Variable: ");
    for (int i = 0; i < variable.length; i++) printf("%c", variable.start[i]);
    printf("\n");

    printf("----[ Value: ");
    for (int i = 0; i < value.length; i++) printf("%c", value.start[i]);
    printf("\n");
}

static void parse_set(Lexer* lexer) {
    Token variable = vl_lexer_next(lexer);
    expect_token(lexer, TOKEN_EQ);
    Token value = vl_lexer_next(lexer);

    printf("Set:\n");
    printf("----[ Variable: ");
    for (int i = 0; i < variable.length; i++) printf("%c", variable.start[i]);
    printf("\n");

    printf("----[ Value: ");
    for (int i = 0; i < value.length; i++) printf("%c", value.start[i]);
    printf("\n");
}

void vl_parser_init(Parser* parser) {
    parser->block_id = 0;
    parser->block_stack_pointer = 0;
}

void vl_parser_parse(Parser* parser, Lexer* lexer) {
    Token current_token = vl_lexer_next(lexer);

    while (current_token.type != TOKEN_EOF) {
        switch (current_token.type) {
            case TOKEN_PUSH: parse_push(lexer); break;
            case TOKEN_SET: parse_set(lexer); break;
        }

        current_token = vl_lexer_next(lexer);
    }
}


