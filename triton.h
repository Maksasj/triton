#ifndef TRITON_H
#define TRITON_H

#include <stdio.h>

#ifndef TRITON_FPRINTF 
    #define TRITON_FPRINTF fprintf
#endif

typedef struct {
    int tail;
    int key;
} triton_scope_t;

#define TRITON_MAX_SCOPES 100

typedef struct {
    FILE* sink;
    triton_scope_t scopes[TRITON_MAX_SCOPES];
    int scope;
} triton_serializer_t;

typedef triton_serializer_t triser_t;

void tri_begin_element(triser_t* tri);
void tri_end_element(triser_t* tri);

void tri_begin_object(triser_t* tri);
void tri_object_end(triser_t* tri);

void tri_begin_array(triser_t* tri);
void tri_end_array(triser_t* tri);

void tri_member_key(triser_t* tri, const char* key);

void tri_null(triser_t* tri);
void tri_bool(triser_t* tri, int value);
void tri_float(triser_t* tri, float value);
void tri_integer(triser_t* tri, int value);
void tri_string(triser_t* tri, const char* value);

#ifdef TRITON_IMPLEMENTATION

triton_scope_t* tri_current_scope(triser_t* tri) {
    return &tri->scopes[tri->scope];
}

void tri_push_scope(triser_t* tri) {
    tri->scopes[tri->scope].tail = 0;
    tri->scopes[tri->scope].key = 1;
    ++tri->scope;
}

void tri_pop_scope(triser_t* tri) {
    --tri->scope;
}

void tri_begin_element(triser_t* tri) {
    triton_scope_t* scope = tri_current_scope(tri);

    if(scope->tail && !scope->key) {
        TRITON_FPRINTF(tri->sink, ",");
    }
}

void tri_end_element(triser_t* tri) {
    triton_scope_t* scope = tri_current_scope(tri);

    scope->tail = 1;
    scope->key = 0;
}

void tri_begin_object(triser_t* tri) {
    tri_begin_element(tri);

    tri_push_scope(tri);
    TRITON_FPRINTF(tri->sink, "{");
    triton_scope_t* scope = tri_current_scope(tri);
    scope->key = 1;
}

void tri_object_end(triser_t* tri) {
    TRITON_FPRINTF(tri->sink, "}");
    
    tri_pop_scope(tri);
    tri_end_element(tri);
}

void tri_begin_array(triser_t* tri) {
    tri_begin_element(tri);
    
    tri_push_scope(tri);
    triton_scope_t* scope = tri_current_scope(tri);
    scope->key = 1;

    TRITON_FPRINTF(tri->sink, "[");
}

void tri_end_array(triser_t* tri) {
    TRITON_FPRINTF(tri->sink, "]");

    tri_pop_scope(tri);
    tri_end_element(tri);
}

void tri_member_key(triser_t* tri, const char* key) {
    triton_scope_t* scope = tri_current_scope(tri);

    tri_begin_element(tri);
    
    TRITON_FPRINTF(tri->sink, "\"%s\":", key);

    tri_end_element(tri);

    scope->key = 1;
}

void tri_null(triser_t* tri) {
    tri_begin_element(tri);
    
    TRITON_FPRINTF(tri->sink, "null");

    tri_end_element(tri);
}

void tri_bool(triser_t* tri, int value) {
    tri_begin_element(tri);

    if(value) {
        TRITON_FPRINTF(tri->sink, "true");
    } else 
        TRITON_FPRINTF(tri->sink, "false");

    tri_end_element(tri);
}

void tri_float(triser_t* tri, float value) {
    tri_begin_element(tri);

    TRITON_FPRINTF(tri->sink, "%f", value);

    tri_end_element(tri);
}

void tri_integer(triser_t* tri, int value) {
    tri_begin_element(tri);

    TRITON_FPRINTF(tri->sink, "%d", value);

    tri_end_element(tri);
}

void tri_string(triser_t* tri, const char* value) {
    tri_begin_element(tri);

    TRITON_FPRINTF(tri->sink, "\"%s\"", value);

    tri_end_element(tri);
}

#endif

#endif