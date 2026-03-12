#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "Includes/parser.h"



char* read_file_to_string(const char* file_name) {
    
    FILE * file = fopen(argv[1], "rb");

    if (!file) {
        printf("Failed to open file.");

        return 1;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);
    
    char * source_code = (char *)malloc(size + 1);

    if (source_code == NULL) {
        printf("Malloc error.");
        fclose(file);

        return 1;
    }

    source_code[size] = (char)0;

    fread(source_code, 1, size, file);
    fclose(file);

    return source_code;
}

int main(int argc, char** argv) {
    if (argc < 3) { printf("Missing arguments.\n"); return 1; }

    Lexer lexer;
    vl_lexer_init(&lexer, "");
    
    vl_parser_parse(&lexer);
}