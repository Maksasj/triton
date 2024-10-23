#ifndef TRITON_H
#define TRITON_H

// json values: number, string, null, array, object

#include <string.h>
#include <ctype.h>

#define HAUL_IMPLEMETATION
#include "vector.h"

// json object
typedef struct {
} triton_object_t;

// json array
typedef struct {
} triton_array_t;

typedef struct {

} triton_value_entry_t;

typedef struct triton_value_t triton_value_t;

typedef struct {

} triton_primitive_t;

struct triton_value_t {
    union {
        triton_primitive_t primitive;

        struct {
            triton_value_t* entries;
            int count;
        } array;

        struct {
            triton_value_entry_t* entries;
            int count;
        } object;
    } as;
};

typedef enum {
    TRITON_TOKEN_LBRACE,  // {
    TRITON_TOKEN_RBRACE,  // }
    TRITON_TOKEN_LBRACKET,// [
    TRITON_TOKEN_RBRACKET,// ]
    TRITON_TOKEN_COLON,   // :
    TRITON_TOKEN_COMMA,   // ,
    TRITON_TOKEN_STRING,  // "some string"
    TRITON_TOKEN_NUMBER,  // 123.45
    TRITON_TOKEN_TRUE,    // true
    TRITON_TOKEN_FALSE,   // false
    TRITON_TOKEN_NULL,    // null
    TRITON_TOKEN_EOF,     // End of file
    TRITON_TOKEN_ERROR    // Parsing error
} triton_token_type_t;

typedef struct {
    triton_token_type_t type;
    char *lexeme;
} triton_token_t;

void triton_skip_whitespace(const char **input) {
    while (isspace(**input)) {
        (*input)++;
    }
}

char *triton_extract_string(const char **input) {
    const char *start = ++(*input);  // Skip the initial "
    while (**input != '"' && **input != '\0') {
        (*input)++;
    }
    if (**input == '\0') {
        return NULL; // Unterminated string
    }

    size_t length = *input - start;
    char *string = malloc(length + 1 + 2);
    string[0] = '"';
    strncpy(string + 1, start, length);
    string[length+1] = '"'; // Todo probably we do not need to do that
    string[length+2] = '\0'; // Todo probably we do not need to do that

    (*input)++;  // Skip the closing "
    return string;
}

triton_token_t triton_next_token(const char **input) {
    triton_skip_whitespace(input);

    triton_token_t token;
    token.lexeme = NULL;

    switch (**input) {
        case '{':
            token.type = TRITON_TOKEN_LBRACE;
            (*input)++;
            break;
        case '}':
            token.type = TRITON_TOKEN_RBRACE;
            (*input)++;
            break;
        case '[':
            token.type = TRITON_TOKEN_LBRACKET;
            (*input)++;
            break;
        case ']':
            token.type = TRITON_TOKEN_RBRACKET;
            (*input)++;
            break;
        case ':':
            token.type = TRITON_TOKEN_COLON;
            (*input)++;
            break;
        case ',':
            token.type = TRITON_TOKEN_COMMA;
            (*input)++;
            break;
        case '"':
            token.type = TRITON_TOKEN_STRING;
            token.lexeme = triton_extract_string(input);
            if (token.lexeme == NULL) {
                token.type = TRITON_TOKEN_ERROR;
            }
            break;
        case '\0':
            token.type = TRITON_TOKEN_EOF;
            break;
        default:
            // Handle numbers, true, false, null
            if (isdigit(**input) || **input == '-') {
                // Parse a number
                const char *start = *input;
                if (**input == '-') (*input)++;
                while (isdigit(**input)) (*input)++;
                if (**input == '.') {
                    (*input)++;
                    while (isdigit(**input)) (*input)++;
                }
                size_t length = *input - start;
                token.lexeme = malloc(length + 1);
                strncpy(token.lexeme, start, length);
                token.lexeme[length] = '\0';
                token.type = TRITON_TOKEN_NUMBER;
            } else if (strncmp(*input, "true", 4) == 0) {
                token.type = TRITON_TOKEN_TRUE;
                (*input) += 4;
            } else if (strncmp(*input, "false", 5) == 0) {
                token.type = TRITON_TOKEN_FALSE;
                (*input) += 5;
            } else if (strncmp(*input, "null", 4) == 0) {
                token.type = TRITON_TOKEN_NULL;
                (*input) += 4;
            } else {
                token.type = TRITON_TOKEN_ERROR;
            }
            break;
    }

    return token;
}

typedef struct {

} triton_json_t;

typedef enum {
    TRITON_OK,
    TRITON_ERROR,
} triton_result_code_t;

typedef struct {
    triton_result_code_t code;
} triton_result_t;

#endif