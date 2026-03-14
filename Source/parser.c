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
#include "Includes/errors.h"

static Token expect_token(Lexer* lexer, TokenType type) {
    Token token = vl_lexer_next(lexer);
    
    if (token.type != type) {
        printf("Parser error: expected '%s', got '%s'.\n", token_type_to_string(type), token_type_to_string(token.type));
        exit(ERR_EXPECTED_GOT);
    }

    return token;
}

static Token seek_token(Lexer* lexer, TokenType type) {
    Token current = vl_lexer_next(lexer);
    for (current; current.type != type; current = vl_lexer_next(lexer)) {
        if (current.type == TOKEN_EOF) {
            printf("Parser error: reached EOF before finding token '%s'.", token_type_to_string(type));
            exit(ERR_SEEK_FOUND_EOF);
        }
    }

    return current;
}

static void enter_code_block(Parser* parser, CodeBlockType type) {
    if (parser->block_stack_pointer == CODE_BLOCK_STACK_SIZE) { /* Fix conflicts later (This check is absurdly idiotic) */
        printf("Parser error: scope overflow.");
        exit(ERR_SCOPE_OVERFLOW);
    }

    parser->code_block_stack[parser->block_stack_pointer++] = (CodeBlock){
        .id = parser->block_id++, 
        .type = type
    };
}

static int current_code_block(Parser* parser) {
    if (parser->block_stack_pointer == 0) return -1; 
    return (int)parser->code_block_stack[parser->block_stack_pointer - 1].id;
}

static void leave_code_block(Parser* parser) {
    if (parser->block_stack_pointer > 0) {
        parser->block_stack_pointer--;
    }
}

static void parse_expression(Parser* parser, Lexer* lexer) {

}

static void parse_push(Parser* parser, Lexer* lexer) {
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

    printf("----[ Scope: %d\n", current_code_block(parser));
}

static void parse_set(Parser* parser, Lexer* lexer) {
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

static void parse_if(Parser* parser, Lexer* lexer) {
    printf("If:\n");
    printf("----[ Scope: %d\n", current_code_block(parser));

    expect_token(lexer, TOKEN_EOL);

    enter_code_block(parser, BLOCK_IF);
}

static void parse_repeat(Parser* parser, Lexer* lexer) {
    printf("Repeat:\n");
    printf("----[ Scope: %d\n", current_code_block(parser));

    expect_token(lexer, TOKEN_EOL);

    enter_code_block(parser, BLOCK_REPEAT);
}

static void parse_asm(Parser* parser, Lexer* lexer) {
    expect_token(lexer, TOKEN_LPAREN);

    Token current = vl_lexer_next(lexer);

    printf("Asm:\n");
    printf("----[ Scope: %d\n", current_code_block(parser));
    for (current; current.type != TOKEN_RPAREN; current = vl_lexer_next(lexer)) {
        if (current.type == TOKEN_STRING) {
            printf("----[ Instruction: %.*s\n", current.length, current.start);
        }
    }
}

static void parse_function(Parser* parser, Lexer* lexer) {
    printf("Function:\n");
    printf("----[ Scope: %d\n", parser->block_id);

    enter_code_block(parser, BLOCK_FUNCTION);
}

static void parse_end(Parser* parser, Lexer* lexer) {
    leave_code_block(parser);
    printf("End:\n");
    printf("----[ Scope: %d\n", current_code_block(parser));
}

void vl_parser_init(Parser* parser) {
    parser->block_id = 0;
    parser->block_stack_pointer = 0;
}

void vl_parser_parse(Parser* parser, Lexer* lexer) {
    Token current_token = vl_lexer_next(lexer);

    while (current_token.type != TOKEN_EOF) {
        switch (current_token.type) {
            case TOKEN_PUSH: parse_push(parser, lexer); break;
            case TOKEN_SET: parse_set(parser, lexer); break;
            case TOKEN_IF: parse_if(parser, lexer); break;
            case TOKEN_END: parse_end(parser, lexer); break;
            case TOKEN_REPEAT: parse_repeat(parser, lexer); break;
            case TOKEN_ASM: parse_asm(parser, lexer); break;
            case TOKEN_FUNCTION: parse_function(parser, lexer); break;
        }

        current_token = vl_lexer_next(lexer);
    }
}


