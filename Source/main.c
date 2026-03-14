/*

    A string is an array of characters that ends at a null character
    Not every array of characters that has a null character is a string
    An array of characters that does not have a null character will never be a string

    Ts just for debugging right now

*/

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "Includes/parser.h"
#include "Includes/utilities.h"
  
char* read_file_to_string(const char* file_name) {
    FILE * file = fopen(file_name, "rb");

    if (!file) { printf("Failed to open file."); return NULL; }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);
    
    char* source_code = (char*)malloc(size + 1);

    if (source_code == NULL) {
        printf("Malloc error.");
        fclose(file);

        return NULL;
    }

    source_code[size] = (char)0;

    fread(source_code, 1, size, file);
    fclose(file);

    return source_code;
}

int main(int argc, char** argv) {
    if (argc < 2) { printf("Missing arguments.\n"); return 1; }

    char* source_file_name = argv[1];
    char* source_code = read_file_to_string(source_file_name);

    Lexer lexer;

    printf("\n[[ TOKENIZING ]]:\n\n");
    
    vl_lexer_init(&lexer, source_code);
    Token token = vl_lexer_next(&lexer);
    while (token.type != TOKEN_EOF) {
        if (token.type == TOKEN_EOL) {
            printf("%s\n", token_type_to_string(token.type));
        } else {
            printf("%s '%.*s'\n", token_type_to_string(token.type), token.length, token.start);
        }
        
        token = vl_lexer_next(&lexer);
    }

    printf("\n[[ PARSING ]]:\n\n");

    Parser parser;
    vl_lexer_init(&lexer, source_code);
    vl_parser_init(&parser);
    vl_parser_parse(&parser, &lexer);

    free(source_code);
}