#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "cmd_utils.h"

int main(int argc, char** argv) {
    if (argc < 3) { printf("Missing arguments.\n"); return 1; }
    
    FILE* file = fopen(argv[1], "rb");
    if (!file) { printf("Failed to open file."); return 1; }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char* source_code = (char*)malloc(size + 1);
    source_code[size] = (char)0;

    if (source_code == NULL) { printf("Malloc error."); fclose(file); return 1; }

    fread(source_code, 1, size, file);
    fclose(file);

    Lexer lexer;
    vl_lexer_init(&lexer, source_code);

    while (1) {
        Token token = vl_lexer_next(&lexer);

        char* token_content = (char*)malloc(token.length + 1); // +1 Null terminator
        memcpy(token_content, token.start, token.length); token_content[token.length] = (char)0;

        if (token.type == TOKEN_EOF) break;

        if (token.length > 0) {
            if (token_content[0] == '\n') continue;
            else {
                printf("%-10.*s: %s", token.length, token.start, tk_type_to_string(token.type)); 
                printf("\n");
            }

            free(token_content);
        }
    }
    
    free(source_code);
}
