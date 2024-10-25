#ifndef TRITON_H
#define TRITON_H

// json values: number, string, null, array, object

#include <string.h>
#include <ctype.h>

#define HAUL_IMPLEMETATION
#include "vector.h"

// Lexer
typedef enum {
    TRITON_TOKEN_LBRACE,  
    TRITON_TOKEN_RBRACE,  
    TRITON_TOKEN_LBRACKET,
    TRITON_TOKEN_RBRACKET,
    TRITON_TOKEN_COLON,   
    TRITON_TOKEN_COMMA,   
    TRITON_TOKEN_STRING,  
    TRITON_TOKEN_NUMBER,  
    TRITON_TOKEN_TRUE,    
    TRITON_TOKEN_FALSE,   
    TRITON_TOKEN_NULL,    
    TRITON_TOKEN_EOF,     
    TRITON_TOKEN_ERROR    
} triton_token_type_t;

typedef struct {
    triton_token_type_t type;
    char *lexeme;
} triton_token_t;

typedef struct {
    const char* input;
    int pointer;
} triton_lexer_t;

void triton_skip_whitespace(triton_lexer_t* lexer);
char *triton_extract_string(triton_lexer_t* lexer);
triton_token_t triton_next_token(triton_lexer_t* lexer);

// Json parsing
typedef struct triton_value_t triton_value_t;
typedef struct triton_value_entry_t triton_value_entry_t;

typedef struct {
    void** items;

    int capacity;
    int count;
} triton_container_base_t;

typedef triton_container_base_t triton_array_t;
typedef triton_container_base_t triton_object_t;

void create_container_base(triton_container_base_t* container_base, int initial_capacity);
void container_base_push(triton_container_base_t* container_base, void* item);
void* container_base_pop(triton_container_base_t* container_base);
void* container_base_get(triton_container_base_t* container_base, int index);
int container_base_empty(triton_container_base_t* container_base);
int container_base_size(triton_container_base_t* container_base);
int container_base_capacity(triton_container_base_t* container_base);
void free_container_base(triton_container_base_t* container_base);
void free_container_base_content(triton_container_base_t* container_base);

void create_triton_array(triton_array_t* triton_array, int initial_capacity);
void triton_array_push(triton_array_t* triton_array, void* item);
triton_value_t* triton_array_pop(triton_array_t* triton_array);
triton_value_t* triton_array_get(triton_array_t* triton_array, int index);
int triton_array_empty(triton_array_t* triton_array);
int triton_array_size(triton_array_t* triton_array);
void free_triton_array(triton_array_t* triton_array);
void free_triton_array_content(triton_array_t* triton_array);

void create_triton_object(triton_object_t* triton_object, int initial_capacity);
void triton_object_push(triton_object_t* triton_object, void* item);
triton_value_entry_t* triton_object_pop(triton_object_t* triton_object);
triton_value_entry_t* triton_object_get(triton_object_t* triton_object, int index);
int triton_object_empty(triton_object_t* triton_object);
int triton_object_size(triton_object_t* triton_object);
void free_triton_object(triton_object_t* triton_object);
void free_triton_object_content(triton_object_t* triton_object);

typedef enum {
    TRITON_NUMBER_VALUE,
    TRITON_STRING_VALUE,
    TRITON_BOOLEAN_VALUE,
    TRITON_NULL_VALUE,
    TRITON_ARRAY_VALUE,
    TRITON_OBJECT_VALUE,
} triton_value_type_t;

#define TRITON_TRUE 1
#define TRITON_FALSE 0

typedef double triton_number_t;
typedef char* triton_string_t;
typedef unsigned char triton_boolean_t;

struct triton_value_t {
    triton_value_type_t type;

    union {
        triton_number_t number;
        triton_string_t string;
        triton_boolean_t boolean;
        triton_array_t array;
        triton_object_t object;
    } as;
};

struct triton_value_entry_t {
    const char* name;
    triton_value_t value;
};

typedef struct {
    triton_value_t value;
} triton_json_t;

typedef enum {
    TRITON_OK,
    TRITON_ERROR
} triton_result_code_t;

typedef struct {
    triton_result_code_t code;
} triton_lex_result_t;

typedef struct {
    triton_result_code_t code;
} triton_parse_result_t;

triton_parse_result_t triton_parse_string(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_number(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_object(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_array(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_true(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_false(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_null(triton_value_t* value, triton_lexer_t* lexer);
triton_parse_result_t triton_parse_value(triton_value_t* value, triton_lexer_t* lexer);

triton_parse_result_t triton_parse_json(triton_json_t* json, const char* string);

// Stringify
void triton_stringify_value(FILE* stream, triton_value_t* value);
void triton_stringify_json(FILE* stream, triton_json_t* json);

#ifdef TRITON_IMPLEMENTATION

void create_container_base(triton_container_base_t* container_base, int initial_capacity) {
    assert(initial_capacity > 0);

    container_base->items = calloc(initial_capacity, sizeof(void*));

    container_base->count = 0;
    container_base->capacity = initial_capacity;
}

void container_base_push(triton_container_base_t* container_base, void* item) {
    if(container_base->count + 1 > container_base->capacity) {
        container_base->capacity = container_base->capacity * 2;

        // Todo check if items is null
        container_base->items = realloc(container_base->items, container_base->capacity * sizeof(void*));
    }

    container_base->items[container_base->count] = item;
    ++container_base->count;
}

void* container_base_pop(triton_container_base_t* container_base) {
    if(container_base->count == 0) {
        return NULL;
    }

    --container_base->count;
    void* popped_value = container_base->items[container_base->count];

    if(container_base->count > 10 && (container_base->count <= container_base->capacity / 2)) {
        container_base->capacity = container_base->capacity / 2;

        // Todo check if items is null
        container_base->items = realloc(container_base->items, container_base->capacity * sizeof(void*));
    }

    return popped_value;
}

void* container_base_get(triton_container_base_t* container_base, int index) {
    if(container_base->count <= index) {
        return NULL;
    }

    return container_base->items[index];
}

int container_base_empty(triton_container_base_t* container_base) {
    return container_base->count == 0;
}

int container_base_size(triton_container_base_t* container_base) {
    return container_base->count;
}

void free_container_base(triton_container_base_t* container_base) {
    free(container_base->items);
}

void free_container_base_content(triton_container_base_t* container_base) {
    for(int i = 0; i < container_base->count; ++i) {
        free(container_base->items[i]);
    }
}

void create_triton_array(triton_array_t* triton_array, int initial_capacity) {
    create_container_base(triton_array, initial_capacity);
}

void triton_array_push(triton_array_t* triton_array, void* item) {
    container_base_push(triton_array, item);
}

triton_value_t* triton_array_pop(triton_array_t* triton_array) {
    return container_base_pop(triton_array);
}

triton_value_t* triton_array_get(triton_array_t* triton_array, int index) {
    return container_base_get(triton_array, index);
}

int triton_array_empty(triton_array_t* triton_array) {
    return container_base_empty(triton_array);
}

int triton_array_size(triton_array_t* triton_array) {
    return container_base_size(triton_array);
}

void free_triton_array(triton_array_t* triton_array) {
    free_container_base(triton_array);
}

void free_triton_array_content(triton_array_t* triton_array) {
    free_container_base_content(triton_array);
}

void create_triton_object(triton_object_t* triton_object, int initial_capacity) {
    create_container_base(triton_object, initial_capacity);
}

void triton_object_push(triton_object_t* triton_object, void* item) {
    container_base_push(triton_object, item);
}

triton_value_entry_t* triton_object_pop(triton_object_t* triton_object) {
    return container_base_pop(triton_object);
}

triton_value_entry_t* triton_object_get(triton_object_t* triton_object, int index) {
    return container_base_get(triton_object, index);
}

int triton_object_empty(triton_object_t* triton_object) {
    return container_base_empty(triton_object);
}

int triton_object_size(triton_object_t* triton_object) {
    return container_base_size(triton_object);
}

void free_triton_object(triton_object_t* triton_object) {
    free_container_base(triton_object);
}

void free_triton_object_content(triton_object_t* triton_object) {
    free_container_base_content(triton_object);
}

// Lexer
void triton_skip_whitespace(triton_lexer_t* lexer) {
    while (isspace(lexer->input[lexer->pointer])) {
        lexer->pointer++;
    }
}

char *triton_extract_string(triton_lexer_t* lexer) {
    int start = ++lexer->pointer;  // Skip the initial ".

    while (lexer->input[lexer->pointer] != '"' && lexer->input[lexer->pointer] != '\0') {
        lexer->pointer++;
    }
    
    if (lexer->input[lexer->pointer] == '\0') {
        return NULL;
    }

    int length = lexer->pointer - start;
    char *string = malloc(length + 1);

    strncpy(string, lexer->input + start, length);
    string[length] = '\0'; // Todo probably we do not need to do that

    lexer->pointer++;  // Skip the closing "
    return string;
}

triton_lex_result_t triton_lex_lbrace(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != '{')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_LBRACE;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_rbrace(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != '}')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_RBRACE;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_lbracket(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != '[')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_LBRACKET;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_rbracket(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != ']')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_RBRACKET;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_colon(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != ':')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_COLON;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_comma(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != ',')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_COMMA;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_string(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] == '"') {
        token->type = TRITON_TOKEN_STRING;
        token->lexeme = triton_extract_string(lexer);

        if (token->lexeme == NULL) {
            token->type = TRITON_TOKEN_ERROR;
        }

        return (triton_lex_result_t) { TRITON_OK };
    }

    return (triton_lex_result_t) { TRITON_ERROR };
}

triton_lex_result_t triton_lex_eof(triton_token_t* token, triton_lexer_t* lexer) {
    if(lexer->input[lexer->pointer] != '\0')
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_EOF;
    token->lexeme = NULL;

    lexer->pointer++;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_number(triton_token_t* token, triton_lexer_t* lexer) {
    if (isdigit(lexer->input[lexer->pointer]) || lexer->input[lexer->pointer] == '-') {
        // Parse a number
        int start = lexer->pointer;
        
        if (lexer->input[lexer->pointer] == '-') 
            lexer->pointer++;
        
        while (isdigit(lexer->input[lexer->pointer])) 
            lexer->pointer++;
        
        if (lexer->input[lexer->pointer] == '.') {
            lexer->pointer++;

            while (isdigit(lexer->input[lexer->pointer])) 
                lexer->pointer++;
        }
        
        int length = lexer->pointer - start;

        token->lexeme = malloc(length + 1);
        strncpy(token->lexeme, &lexer->input[start], length);

        token->lexeme[length] = '\0';
        token->type = TRITON_TOKEN_NUMBER;

        return (triton_lex_result_t) { TRITON_OK };
    }

    return (triton_lex_result_t) { TRITON_ERROR };
}

triton_lex_result_t triton_lex_true(triton_token_t* token, triton_lexer_t* lexer) {
    if(strncmp(lexer->input + lexer->pointer, "true", 4) != 0)
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_TRUE;
    token->lexeme = NULL;

    lexer->pointer += 4;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_false(triton_token_t* token, triton_lexer_t* lexer) {
    if(strncmp(lexer->input + lexer->pointer, "false", 5) != 0)
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_FALSE;
    token->lexeme = NULL;

    lexer->pointer += 5;

    return (triton_lex_result_t) { TRITON_OK };
}

triton_lex_result_t triton_lex_null(triton_token_t* token, triton_lexer_t* lexer) {
    if(strncmp(lexer->input + lexer->pointer, "null", 4) != 0)
        return (triton_lex_result_t) { TRITON_ERROR };

    token->type = TRITON_TOKEN_NULL;
    token->lexeme = NULL;

    lexer->pointer += 4;
    
    return (triton_lex_result_t) { TRITON_OK };
}

triton_token_t triton_next_token(triton_lexer_t* lexer) {
    triton_skip_whitespace(lexer);

    triton_token_t token;
    token.type = TRITON_TOKEN_ERROR;
    token.lexeme = NULL;

    if(triton_lex_lbrace(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_rbrace(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_lbracket(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_rbracket(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_colon(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_comma(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_string(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_eof(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_number(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_true(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_false(&token, lexer).code == TRITON_OK)
        return token;
    
    if(triton_lex_null(&token, lexer).code == TRITON_OK)
        return token;
    
    return token;
    
    switch (lexer->input[lexer->pointer]) {
        case '{':
            token.type = TRITON_TOKEN_LBRACE;
            lexer->pointer++;
            break;
        case '}':
            token.type = TRITON_TOKEN_RBRACE;
            lexer->pointer++;
            break;
        case '[':
            token.type = TRITON_TOKEN_LBRACKET;
            lexer->pointer++;
            break;
        case ']':
            token.type = TRITON_TOKEN_RBRACKET;
            lexer->pointer++;
            break;
        case ':':
            token.type = TRITON_TOKEN_COLON;
            lexer->pointer++;
            break;
        case ',':
            token.type = TRITON_TOKEN_COMMA;
            lexer->pointer++;
            break;
        case '"':
            token.type = TRITON_TOKEN_STRING;
            token.lexeme = triton_extract_string(lexer);
            if (token.lexeme == NULL) {
                token.type = TRITON_TOKEN_ERROR;
            }
            break;
        case '\0':
            token.type = TRITON_TOKEN_EOF;
            break;
        default:
            // Handle numbers, true, false, null
            if (isdigit(lexer->input[lexer->pointer]) || lexer->input[lexer->pointer] == '-') {
                // Parse a number
                int start = lexer->pointer;
                
                if (lexer->input[lexer->pointer] == '-') 
                    lexer->pointer++;
                
                while (isdigit(lexer->input[lexer->pointer])) 
                    lexer->pointer++;
                
                if (lexer->input[lexer->pointer] == '.') {
                    lexer->pointer++;

                    while (isdigit(lexer->input[lexer->pointer])) 
                        lexer->pointer++;
                }
                
                int length = lexer->pointer - start;

                token.lexeme = malloc(length + 1);
                strncpy(token.lexeme, &lexer->input[start], length);

                token.lexeme[length] = '\0';
                token.type = TRITON_TOKEN_NUMBER;
            } else if (strncmp(lexer->input + lexer->pointer, "true", 4) == 0) {
                token.type = TRITON_TOKEN_TRUE;
                token.lexeme = "true";
                
                lexer->pointer += 4;
            } else if (strncmp(lexer->input + lexer->pointer, "false", 5) == 0) {
                token.type = TRITON_TOKEN_FALSE;
                token.lexeme = "false";
                
                lexer->pointer += 5;
            } else if (strncmp(lexer->input + lexer->pointer, "null", 4) == 0) {
                token.type = TRITON_TOKEN_NULL;
                token.lexeme = "null";

                lexer->pointer += 4;
            } else {
                token.type = TRITON_TOKEN_ERROR;
            }

            break;
    }

    return token;
}

// Parser
triton_parse_result_t triton_parse_token(triton_lexer_t* lexer, triton_token_type_t type) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == type) {
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_string(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_STRING) {
        value->type = TRITON_STRING_VALUE;
        value->as.string = token.lexeme;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_number(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_NUMBER) {
        value->type = TRITON_NUMBER_VALUE;
        value->as.number = 1.0f;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_object(triton_value_t* value, triton_lexer_t* lexer) {
    if(triton_parse_token(lexer, TRITON_TOKEN_LBRACE).code == TRITON_ERROR)
        return (triton_parse_result_t) { TRITON_ERROR };

    triton_object_t object;
    create_triton_array(&object, 10);

    int i = 0;
    for(;;++i) {
        if(i != 0 && triton_parse_token(lexer, TRITON_TOKEN_COMMA).code == TRITON_ERROR)
            break;
        
        triton_value_t key_value;
        triton_parse_result_t key_result = triton_parse_string(&key_value, lexer);

        if(key_result.code == TRITON_ERROR)
            break;

        if(triton_parse_token(lexer, TRITON_TOKEN_COLON).code == TRITON_ERROR)
            break;

        triton_value_t entry_value;
        triton_parse_result_t value_result = triton_parse_value(&entry_value, lexer);

        if(value_result.code == TRITON_ERROR)
            break;

        triton_value_entry_t* actual = (triton_value_entry_t*) malloc(sizeof(triton_value_entry_t));
        actual->name = key_value.as.string;
        actual->value = entry_value;
        triton_array_push(&object, actual);
    }

    if(triton_parse_token(lexer, TRITON_TOKEN_RBRACE).code == TRITON_ERROR) {
        free_triton_array(&object); // Todo
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    value->type = TRITON_OBJECT_VALUE;
    value->as.object = object;

    return (triton_parse_result_t) { TRITON_OK };
}

triton_parse_result_t triton_parse_array(triton_value_t* value, triton_lexer_t* lexer) {
    if(triton_parse_token(lexer, TRITON_TOKEN_LBRACKET).code == TRITON_ERROR)
        return (triton_parse_result_t) { TRITON_ERROR };

    triton_array_t array;
    create_triton_array(&array, 10);

    int i = 0;
    for(;;++i) {
        if(i != 0 && triton_parse_token(lexer, TRITON_TOKEN_COMMA).code == TRITON_ERROR)
            break;

        triton_value_t entry_value;
        triton_parse_result_t result = triton_parse_value(&entry_value, lexer);

        if(result.code == TRITON_ERROR)
            break;

        triton_value_t* actual = (triton_value_t*) malloc(sizeof(triton_value_t));
        *actual = entry_value;
        triton_array_push(&array, actual);
    }

    if(triton_parse_token(lexer, TRITON_TOKEN_RBRACKET).code == TRITON_ERROR) {
        free_triton_array(&array); // Todo
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    value->type = TRITON_ARRAY_VALUE;
    value->as.array = array;

    return (triton_parse_result_t) { TRITON_OK };
}

triton_parse_result_t triton_parse_true(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_TRUE) {
        value->type = TRITON_BOOLEAN_VALUE;
        value->as.boolean = TRITON_TRUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_false(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_FALSE) {
        value->type = TRITON_BOOLEAN_VALUE;
        value->as.boolean = TRITON_FALSE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_null(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_NULL) {
        value->type = TRITON_NULL_VALUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_value(triton_value_t* value, triton_lexer_t* lexer) {
    if(triton_parse_string(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_number(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_object(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_array(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_true(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_false(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    if(triton_parse_null(value, lexer).code == TRITON_OK) {
        
        return (triton_parse_result_t) { TRITON_OK };
    }

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_json(triton_json_t* json, const char* string) {
    const char *input = string;

    triton_lexer_t lexer = (triton_lexer_t) {
        .input   = string,
        .pointer = 0
    };

    return triton_parse_value(&json->value, &lexer);
}

// Stringify
void triton_stringify_value(FILE* stream, triton_value_t* value) {
    if(value->type == TRITON_STRING_VALUE) {
        fprintf(stream, "\"%s\"", value->as.string);
        return;
    }

    if(value->type == TRITON_NUMBER_VALUE) {
        fprintf(stream, "%f", value->as.number);
        return;
    }

    if(value->type == TRITON_BOOLEAN_VALUE) {
        if(value->as.boolean)
            fprintf(stream, "true");
        else 
            fprintf(stream, "false");
        
        return;
    }

    if(value->type == TRITON_NULL_VALUE) {
        fprintf(stream, "null");
        return;
    }

    if(value->type == TRITON_ARRAY_VALUE) {
        int count = value->as.array.count;

        fprintf(stream, "[ ");

        for(int i = 0; i < count; ++i) {
            if( i != 0)
                fprintf(stream, ", ");

            triton_stringify_value(stream, triton_array_get(&value->as.array, i));
        }

        fprintf(stream, " ]");

        return;
    }

    if(value->type == TRITON_OBJECT_VALUE) {
        int count = value->as.object.count;

        fprintf(stream, "{ ");

        for(int i = 0; i < count; ++i) {
            if( i != 0)
                fprintf(stream, ", ");

            triton_value_entry_t* value_entry = triton_object_get(&value->as.object, i);
            
            fprintf(stream, "%s: ", value_entry->name);

            triton_stringify_value(stream, &value_entry->value);
        }

        fprintf(stream, " }");

        return;
    }
}

void triton_stringify_json(FILE* stream, triton_json_t* json) {
    triton_stringify_value(stream, &json->value);
}

#endif

#endif