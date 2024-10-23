#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

#include "test.h"

int lex_token_lbrace() {
    const char *json = "{";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_LBRACE);
    return OK;
}

int lex_token_rbrace() {
    const char *json = "}";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_RBRACE);

    return OK;
}

int lex_token_lbracket() {
    const char *json = "[";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_LBRACKET);
    return OK;
}

int lex_token_rbracket() {
    const char *json = "]";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_RBRACKET);
    return OK;
}

int lex_token_colon() {
    const char *json = ":";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_COLON);
    return OK;
}

int lex_token_comma() {
    const char *json = ",";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_COMMA);
    return OK;
}

int lex_token_string() {
    const char *json = "\"some string\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    return OK;
}

int lex_token_number() {
    const char *json = "100.2";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    return OK;
}

int lex_token_true() {
    const char *json = "true";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_TRUE);
    return OK;
}

int lex_token_false() {
    const char *json = "false";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_FALSE);
    return OK;
}

int lex_token_null() {
    const char *json = "null";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NULL);
    return OK;
}

int lex_token_eof() {
    const char *json = "\0";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_EOF);

    return OK;
}

int lex_number_0eplus1() {
    const char *json = "0e+1";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_0e1() {
    const char *json = "0e1";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_after_space() {
    const char *json = " 4";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);
    return OK;
}

int lex_number_double_close_to_zero() {
    const char *json = "-0.000000000000000000000000000000000000000000000000000000000000000000000000000001";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_int_with_exp() {
    const char *json = "20e1";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_minus_zero() {
    const char *json = "-0";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_negative_int() {
    const char *json = "-123";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_negative_one() {
    const char *json = "-1";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_negative_zero() {
    const char *json = "-0";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_capital_e_neg_exp() {
    const char *json = "1E-2";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_capital_e_pos_exp() {
    const char *json = "1E+2";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_capital_e() {
    const char *json = "1E22";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_exponent() {
    const char *json = "123e45";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_fraction_exponent() {
    const char *json = "123.456e78";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_neg_exp() {
    const char *json = "1e-2";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_real_pos_exponent() {
    const char *json = "1e+2";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_simple_int() {
    const char *json = "123";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number_simple_real() {
    const char *json = "123.456789";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_number() {
    const char *json = "123e65";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
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
    RUN_TEST(lex_number_0eplus1);
    RUN_TEST(lex_number_0e1);
    RUN_TEST(lex_number_after_space);
    RUN_TEST(lex_number_double_close_to_zero);
    RUN_TEST(lex_number_int_with_exp);
    RUN_TEST(lex_number_minus_zero);
    RUN_TEST(lex_number_negative_int);
    RUN_TEST(lex_number_negative_one);
    RUN_TEST(lex_number_negative_zero);
    RUN_TEST(lex_number_real_capital_e_neg_exp);
    RUN_TEST(lex_number_real_capital_e_pos_exp);
    RUN_TEST(lex_number_real_capital_e);
    RUN_TEST(lex_number_real_exponent);
    RUN_TEST(lex_number_real_fraction_exponent);
    RUN_TEST(lex_number_real_neg_exp);
    RUN_TEST(lex_number_real_pos_exponent);
    RUN_TEST(lex_number_simple_int);
    RUN_TEST(lex_number_simple_real);
    RUN_TEST(lex_number);

    return 0;
}