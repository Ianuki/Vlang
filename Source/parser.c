#include "Includes/lexer.h"
#include "Includes/parser.h"

void vl_parser_parse(Lexer* lexer) {
    Token current_token = vl_lexer_next(lexer);

    switch (current_token.type) {
        case TOKEN_PUSH:
            Token identifier = vl_lexer_next(lexer);
            Token type = vl_lexer_next(lexer);
    }
}


