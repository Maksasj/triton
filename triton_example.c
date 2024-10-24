#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "triton.h"

int main() {
    const char *string = "{\"key\": \"value\", \"number\": 123, \"flag\": true}";

    triton_json_t json;
    if(triton_parse_json(&json, string).code == TRITON_OK) 
        printf("Parsed json\n");
    else
        printf("Failed to parse json\n");

    /*
    const char *input = json;
    triton_token_t token;
    do {
        token = triton_next_token(&input);
        printf("triton_token_t type: %d, Lexeme: %s\n", token.type, token.lexeme ? token.lexeme : "N/A");

        if (token.lexeme) {
            free(token.lexeme);
        }
    } while (token.type != TRITON_TOKEN_EOF && token.type != TRITON_TOKEN_ERROR);
    */

    return 0;
}