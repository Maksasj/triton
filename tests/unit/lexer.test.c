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

int lex_string_1_2_3_bytes_UTF_minus_8_sequences() {
    const char *json = "\"\\u0060\\u012a\\u12AB\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_accepted_surrogate_pair() {
    const char *json = "\"\\uD801\\udc37\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_accepted_surrogate_pairs() {
    const char *json = "\"\\ud83d\\ude39\\ud83d\\udc8d\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_allowed_escapes() {
    const char *json = "\"\"\\\\/\b\f\n\r\t\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_backslash_and_u_escaped_zero() {
    const char *json = "\"\\\\u0000\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_backslash_doublequotes() {
    const char *json = "\"\"\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_comments() {
    const char *json = "\"a/*b*/c/*d//e\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_double_escape_a() {
    const char *json = "\"\\a\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_double_escape_n() {
    const char *json = "\"\\n\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_escaped_control_character() {
    const char *json = "\"\\u0012\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_escaped_noncharacter() {
    const char *json = "\"\\uFFFF\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_in_array() {
    const char *json = "\"asd\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_in_array_with_leading_space() {
    const char *json = "\"asd\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_last_surrogates_1_and_2() {
    const char *json = "\"\\uDBFF\\uDFFF\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_nbsp_uescaped() {
    const char *json = "\"new\\u00A0line\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_nonCharacterInUTF_minus_8_U_plus_10FFFF() {
    const char *json = "\"􏿿\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_nonCharacterInUTF_minus_8_U_plus_FFFF() {
    const char *json = "\"￿\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_null_escape() {
    const char *json = "\"\\u0000\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_one_minus_byte_minus_utf_minus_8() {
    const char *json = "\"\\u002c\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_pi() {
    const char *json = "\"π\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_reservedCharacterInUTF_minus_8_U_plus_1BFFF() {
    const char *json = "\"𛿿\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_simple_ascii() {
    const char *json = "\"asd \"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_space() {
    const char *json = "\" \"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF() {
    const char *json = "\"\\uD834\\uDd1e\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_three_minus_byte_minus_utf_minus_8() {
    const char *json = "\"\\u0821\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_two_minus_byte_minus_utf_minus_8() {
    const char *json = "\"\\u0123\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_u_plus_2028_line_sep() {
    const char *json = "\" \"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_u_plus_2029_par_sep() {
    const char *json = "\" \"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_uEscape() {
    const char *json = "\"\\u0061\\u30af\\u30EA\\u30b9\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_uescaped_newline() {
    const char *json = "\"new\\u000Aline\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unescaped_char_delete() {
    const char *json = "\"\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode() {
    const char *json = "\"⍂㈴⍂\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicodeEscapedBackslash() {
    const char *json = "\"\\u005C\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_2() {
    const char *json = "\"\\uD83F\\uDFFE\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_10FFFE_nonchar() {
    const char *json = "\"\\uDBFF\\uDFFE\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_1FFFE_nonchar() {
    const char *json = "\"\\uDBFF\\uDFFE\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE() {
    const char *json = "\"\\u200B\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_2064_invisible__plus_() {
    const char *json = "\"\\u2064\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_FDD0_nonchar() {
    const char *json = "\"\\uFDD0\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_U_plus_FFFE_nonchar() {
    const char *json = "\"\\uFFFE\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_unicode_escaped_double_quote() {
    const char *json = "\"\\u005C\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_utf8() {
    const char *json = "\"€𝄞\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, json);

    return OK;
}

int lex_string_with_del_character() {
    const char *json = "\"aa\"";
    const char *ptr = json;

    triton_token_t token = triton_next_token(&ptr);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
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

    // Number literals
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

    // String literals
    RUN_TEST(lex_string_1_2_3_bytes_UTF_minus_8_sequences);
    RUN_TEST(lex_string_accepted_surrogate_pair);
    RUN_TEST(lex_string_accepted_surrogate_pairs);
    RUN_TEST(lex_string_allowed_escapes);
    RUN_TEST(lex_string_backslash_and_u_escaped_zero);
    RUN_TEST(lex_string_backslash_doublequotes);
    RUN_TEST(lex_string_comments);
    RUN_TEST(lex_string_double_escape_a);
    RUN_TEST(lex_string_double_escape_n);
    RUN_TEST(lex_string_escaped_control_character);
    RUN_TEST(lex_string_escaped_noncharacter);
    RUN_TEST(lex_string_in_array);
    RUN_TEST(lex_string_in_array_with_leading_space);
    RUN_TEST(lex_string_last_surrogates_1_and_2);
    RUN_TEST(lex_string_nbsp_uescaped);
    RUN_TEST(lex_string_nonCharacterInUTF_minus_8_U_plus_10FFFF);
    RUN_TEST(lex_string_nonCharacterInUTF_minus_8_U_plus_FFFF);
    RUN_TEST(lex_string_null_escape);
    RUN_TEST(lex_string_one_minus_byte_minus_utf_minus_8);
    RUN_TEST(lex_string_pi);
    RUN_TEST(lex_string_reservedCharacterInUTF_minus_8_U_plus_1BFFF);
    RUN_TEST(lex_string_simple_ascii);
    RUN_TEST(lex_string_space);
    RUN_TEST(lex_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF);
    RUN_TEST(lex_string_three_minus_byte_minus_utf_minus_8);
    RUN_TEST(lex_string_two_minus_byte_minus_utf_minus_8);
    RUN_TEST(lex_string_u_plus_2028_line_sep);
    RUN_TEST(lex_string_u_plus_2029_par_sep);
    RUN_TEST(lex_string_uEscape);
    RUN_TEST(lex_string_uescaped_newline);
    RUN_TEST(lex_string_unescaped_char_delete);
    RUN_TEST(lex_string_unicode);
    RUN_TEST(lex_string_unicodeEscapedBackslash);
    RUN_TEST(lex_string_unicode_2);
    RUN_TEST(lex_string_unicode_U_plus_10FFFE_nonchar);
    RUN_TEST(lex_string_unicode_U_plus_1FFFE_nonchar);
    RUN_TEST(lex_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE);
    RUN_TEST(lex_string_unicode_U_plus_2064_invisible__plus_);
    RUN_TEST(lex_string_unicode_U_plus_FDD0_nonchar);
    RUN_TEST(lex_string_unicode_U_plus_FFFE_nonchar);
    RUN_TEST(lex_string_unicode_escaped_double_quote);
    RUN_TEST(lex_string_utf8);
    RUN_TEST(lex_string_with_del_character);

    return 0;
}