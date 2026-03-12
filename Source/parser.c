#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Includes/lexer.h"
#include "Includes/parser.h"

static void expect_token(Lexer* lexer, TokenType type) {
    Token token = vl_lexer_next(lexer);
    
    if (token.type != type) {
        printf("Parser error: expected %d, got %d.\n", type, token.type);
        exit(1);
    }
}

void vl_parser_parse(Lexer* lexer) {
    Token current_token = vl_lexer_next(lexer);

    while (current_token.type != TOKEN_EOF) {
        switch (current_token.type) {
            case TOKEN_PUSH:
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

                break;
            case TOKEN_SET:
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

                break;
        }

        current_token = vl_lexer_next(lexer);
    }
}


