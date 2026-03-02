#ifndef X86_64_GEN_H
#define X86_64_GEN_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    UINT8,
    UINT16,
    UINT32,
    UINT64
} DataTypes;

typedef struct {
    DataTypes type;
    size_t offset;
} Variable;

const char* data_type_to_string(DataTypes type) {
    switch (type) {
        case UINT8:
            return "byte"; break;
        case UINT16:
            return "word"; break;
        case UINT32:
            return "dword"; break;
        case UINT64:
            return "qword"; break;
        default:
            return "byte";
    }
}

void x86_64_init_stackframe(FILE* output, size_t stack_size) {
    fprintf(output, "\tpush rbp        \n");
    fprintf(output, "\tmov rbp, rsp    \n");
    fprintf(output, "\tsub rsp, %zu    \n", stack_size);
}

void x86_64_set_variable(FILE* output, Variable variable, const char* value) {
    const char* data_type = data_type_to_string(variable.type);

    fprintf(output, "\r\tmov %s [rbp - %zu], %s\n", data_type, variable.offset, value);
}

#endif /* X86_64_GEN_H */