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

typedef struct {
    const char* name;
    triton_value_t* value;
} triton_value_entry_t;

typedef struct {

} triton_primitive_t;

typedef enum {
    TRITON_PRIMITIVE_VALUE,
    TRITON_ARRAY_VALUE,
    TRITON_OBJECT_VALUE,
} triton_value_type_t;

struct triton_value_t {
    triton_value_type_t type;

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

typedef struct {
    triton_value_t value;
} triton_json_t;

typedef enum {
    TRITON_OK,
    TRITON_ERROR
} triton_result_code_t;

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

#ifdef TRITON_IMPLEMENTATION

// Lexer
void triton_skip_whitespace(triton_lexer_t* lexer) {
    while (isspace(lexer->input[lexer->pointer])) {
        lexer->pointer++;
    }
}

char *triton_extract_string(triton_lexer_t* lexer) {
    int start = ++lexer->pointer;  // Skip the initial "
    while (lexer->input[lexer->pointer] != '"' && lexer->input[lexer->pointer] != '\0') {
        lexer->pointer++;
    }
    if (lexer->input[lexer->pointer] == '\0') {
        return NULL; // Unterminated string
    }

    int length = lexer->pointer - start;
    char *string = malloc(length + 1 + 2);
    string[0] = '"';
    strncpy(string + 1, lexer->input + start, length);
    string[length+1] = '"'; // Todo probably we do not need to do that
    string[length+2] = '\0'; // Todo probably we do not need to do that

    lexer->pointer++;  // Skip the closing "
    return string;
}

triton_token_t triton_next_token(triton_lexer_t* lexer) {
    triton_skip_whitespace(lexer);

    triton_token_t token;
    token.lexeme = NULL;

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
                if (lexer->input[lexer->pointer] == '-') lexer->pointer++;
                while (isdigit(lexer->input[lexer->pointer])) lexer->pointer++;
                if (lexer->input[lexer->pointer] == '.') {
                    lexer->pointer++;
                    while (isdigit(lexer->input[lexer->pointer])) lexer->pointer++;
                }
                int length = lexer->pointer - start;
                token.lexeme = malloc(length + 1);
                strncpy(token.lexeme, lexer->input + lexer->pointer, length);
                token.lexeme[length] = '\0';
                token.type = TRITON_TOKEN_NUMBER;
            } else if (strncmp(lexer->input + lexer->pointer, "true", 4) == 0) {
                token.type = TRITON_TOKEN_TRUE;
                lexer->pointer += 4;
            } else if (strncmp(lexer->input + lexer->pointer, "false", 5) == 0) {
                token.type = TRITON_TOKEN_FALSE;
                lexer->pointer += 5;
            } else if (strncmp(lexer->input + lexer->pointer, "null", 4) == 0) {
                token.type = TRITON_TOKEN_NULL;
                lexer->pointer += 4;
            } else {
                token.type = TRITON_TOKEN_ERROR;
            }

            break;
    }

    return token;
}

// Parser
triton_parse_result_t triton_parse_string(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_STRING) {
        value->type = TRITON_PRIMITIVE_VALUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_number(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_NUMBER) {
        value->type = TRITON_PRIMITIVE_VALUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_object(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);
    
    if(token.type != TRITON_TOKEN_LBRACE) {
        *lexer = backup;
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    int i = 0;
    for(;;++i) {
        // if(i != 0) {
        //     backup = *lexer;
        //     token = triton_next_token(lexer);
// 
        //     if(token.type != TRITON_TOKEN_COMMA) {
        //         *lexer = backup;
        //         break;
        //     }
        // }
// 
        // backup = *lexer;
        // triton_parse_result_t result = triton_parse_value(value, lexer);
// 
        // if(result.code == TRITON_ERROR) {
        //     *lexer = backup;
        //     break;
        // }

        break;
    }

    backup = *lexer;
    token = triton_next_token(lexer);
    if(token.type != TRITON_TOKEN_RBRACE) {
        *lexer = backup;
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    value->type = TRITON_OBJECT_VALUE;

    value->as.object.count = i;
    value->as.object.entries = NULL; // Todo

    return (triton_parse_result_t) { TRITON_OK };
}

triton_parse_result_t triton_parse_array(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);
    
    if(token.type != TRITON_TOKEN_LBRACKET) {
        *lexer = backup;
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    int i = 0;
    for(;;++i) {
        if(i != 0) {
            backup = *lexer;
            token = triton_next_token(lexer);

            if(token.type != TRITON_TOKEN_COMMA) {
                *lexer = backup;
                break;
            }
        }

        backup = *lexer;
        triton_parse_result_t result = triton_parse_value(value, lexer);

        if(result.code == TRITON_ERROR) {
            *lexer = backup;
            break;
        }
    }

    backup = *lexer;
    token = triton_next_token(lexer);
    if(token.type != TRITON_TOKEN_RBRACKET) {
        *lexer = backup;
        return (triton_parse_result_t) { TRITON_ERROR };
    }

    value->type = TRITON_ARRAY_VALUE;

    value->as.array.count = i;
    value->as.array.entries = NULL; // Todo

    return (triton_parse_result_t) { TRITON_OK };
}

triton_parse_result_t triton_parse_true(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_TRUE) {
        value->type = TRITON_PRIMITIVE_VALUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_false(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_FALSE) {
        value->type = TRITON_PRIMITIVE_VALUE;
        return (triton_parse_result_t) { TRITON_OK };
    }
    
    *lexer = backup;

    return (triton_parse_result_t) { TRITON_ERROR };
}

triton_parse_result_t triton_parse_null(triton_value_t* value, triton_lexer_t* lexer) {
    triton_lexer_t backup = *lexer;

    triton_token_t token = triton_next_token(lexer);

    if(token.type == TRITON_TOKEN_NULL) {
        value->type = TRITON_PRIMITIVE_VALUE;
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

#endif

#endif