#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

#include "test.h"

int lex_token_lbrace() {
    const char *json = "{";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_LBRACE);
}

int lex_token_rbrace() {
    const char *json = "}";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_RBRACE);
}

int lex_token_lbracket() {
    const char *json = "[";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_LBRACKET);
}

int lex_token_rbracket() {
    const char *json = "]";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_RBRACKET);
}

int lex_token_colon() {
    const char *json = ":";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_COLON);
}

int lex_token_comma() {
    const char *json = ",";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_COMMA);
}

int lex_token_string() {
    const char *json = "\"some string\"";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
}

int lex_token_number() {
    const char *json = "100.2";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
}

int lex_token_true() {
    const char *json = "true";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_TRUE);
}

int lex_token_false() {
    const char *json = "false";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_FALSE);
}

int lex_token_null() {
    const char *json = "null";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_NULL);
}

int lex_token_eof() {
    const char *json = "\0";
    triton_token_t token = triton_next_token(&json);

    return ENSURE_EQ(token.type, TRITON_TOKEN_EOF);
}

int main() {
    // Simple tokens
    RUN_TEST(lex_token_lbrace);
    RUN_TEST(lex_token_rbrace);
    RUN_TEST(lex_token_lbracket);
    RUN_TEST(lex_token_rbracket);
    RUN_TEST(lex_token_colon);
    RUN_TEST(lex_token_comma);
    RUN_TEST(lex_token_string);
    RUN_TEST(lex_token_number);
    RUN_TEST(lex_token_true);
    RUN_TEST(lex_token_false);
    RUN_TEST(lex_token_null);
    RUN_TEST(lex_token_eof);

    // Literals

    return 0;
}