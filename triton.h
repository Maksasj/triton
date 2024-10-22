#ifndef TRITON_H
#define TRITON_H

#include <stdio.h>

typedef struct {
    FILE* sink;
    int scope;
} Triton;

void tri_scope(Triton* tri) {
    for(int i = 0; i < tri->scope; ++i)
        fprintf(tri->sink, "    ");
}

void tri_begin_object(Triton* tri) {
    fprintf(tri->sink, "{\n");
    ++tri->scope;
}

void tri_object_end(Triton* tri) {
    --tri->scope;
    tri_scope(tri);
    fprintf(tri->sink, "}\n");
}

void tri_begin_array(Triton* tri) {
    fprintf(tri->sink, "[\n");
    ++tri->scope;
}

void tri_array_end(Triton* tri) {
    --tri->scope;
    tri_scope(tri);
    fprintf(tri->sink, "]\n");
}

void tri_member_key(Triton* tri, const char* key) {
    tri_scope(tri);

    fprintf(tri->sink, "\"%s\": ", key);
}

void tri_bool(Triton* tri, unsigned char value) {
    if(value) {
        fprintf(tri->sink, "true,\n");
    } else 
        fprintf(tri->sink, "false,\n");
}

void tri_integer(Triton* tri, int value) {
    tri_scope(tri);
    fprintf(tri->sink, "%d,\n", value);
}

#endif