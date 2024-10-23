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
    TOKEN_LBRACE,  // {
    TOKEN_RBRACE,  // }
    TOKEN_LBRACKET,// [
    TOKEN_RBRACKET,// ]
    TOKEN_COLON,   // :
    TOKEN_COMMA,   // ,
    TOKEN_STRING,  // "some string"
    TOKEN_NUMBER,  // 123.45
    TOKEN_TRUE,    // true
    TOKEN_FALSE,   // false
    TOKEN_NULL,    // null
    TOKEN_EOF,     // End of file
    TOKEN_ERROR    // Parsing error
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;
} Token;

void skip_whitespace(const char **input) {
    while (isspace(**input)) {
        (*input)++;
    }
}

char *extract_string(const char **input) {
    const char *start = ++(*input);  // Skip the initial "
    while (**input != '"' && **input != '\0') {
        (*input)++;
    }
    if (**input == '\0') {
        return NULL; // Unterminated string
    }

    size_t length = *input - start;
    char *string = malloc(length + 1);
    strncpy(string, start, length);
    string[length] = '\0';

    (*input)++;  // Skip the closing "
    return string;
}

Token next_token(const char **input) {
    skip_whitespace(input);

    Token token;
    token.lexeme = NULL;

    switch (**input) {
        case '{':
            token.type = TOKEN_LBRACE;
            (*input)++;
            break;
        case '}':
            token.type = TOKEN_RBRACE;
            (*input)++;
            break;
        case '[':
            token.type = TOKEN_LBRACKET;
            (*input)++;
            break;
        case ']':
            token.type = TOKEN_RBRACKET;
            (*input)++;
            break;
        case ':':
            token.type = TOKEN_COLON;
            (*input)++;
            break;
        case ',':
            token.type = TOKEN_COMMA;
            (*input)++;
            break;
        case '"':
            token.type = TOKEN_STRING;
            token.lexeme = extract_string(input);
            if (token.lexeme == NULL) {
                token.type = TOKEN_ERROR;
            }
            break;
        case '\0':
            token.type = TOKEN_EOF;
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
                token.type = TOKEN_NUMBER;
            } else if (strncmp(*input, "true", 4) == 0) {
                token.type = TOKEN_TRUE;
                (*input) += 4;
            } else if (strncmp(*input, "false", 5) == 0) {
                token.type = TOKEN_FALSE;
                (*input) += 5;
            } else if (strncmp(*input, "null", 4) == 0) {
                token.type = TOKEN_NULL;
                (*input) += 4;
            } else {
                token.type = TOKEN_ERROR;
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