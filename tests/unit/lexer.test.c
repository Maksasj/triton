#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

#include "test.h"

int lexer_token_lbrace() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_LBRACE);
    return OK;
}

int lexer_token_rbrace() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "}",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_RBRACE);

    return OK;
}

int lexer_token_lbracket() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_LBRACKET);
    return OK;
}

int lexer_token_rbracket() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "]",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_RBRACKET);
    return OK;
}

int lexer_token_colon() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ":",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_COLON);
    return OK;
}

int lexer_token_comma() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ",",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_COMMA);
    return OK;
}

int lexer_token_string() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"some string\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    return OK;
}

int lexer_token_number() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "100.2",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    return OK;
}

int lexer_token_true() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "true",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_TRUE);
    return OK;
}

int lexer_token_false() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "false",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_FALSE);
    return OK;
}

int lexer_token_null() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "null",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NULL);
    return OK;
}

int lexer_token_eof() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\0",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_EOF);

    return OK;
}

int lexer_number_0eplus1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0e+1",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_0e1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0e1",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_after_space() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = " 4",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);
    return OK;
}

int lexer_number_double_close_to_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-0.000000000000000000000000000000000000000000000000000000000000000000000000000001",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_int_with_exp() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "20e1",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_minus_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-0",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_negative_int() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-123",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_negative_one() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-1",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_negative_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-0",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_capital_e_neg_exp() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1E-2",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_capital_e_pos_exp() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1E+2",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_capital_e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1E22",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_exponent() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123e45",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_fraction_exponent() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123.456e78",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_neg_exp() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1e-2",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_real_pos_exponent() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1e+2",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_simple_int() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number_simple_real() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123.456789",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_number() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123e65",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_1_2_3_bytes_UTF_minus_8_sequences() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0060\\u012a\\u12AB\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_accepted_surrogate_pair() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD801\\udc37\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_accepted_surrogate_pairs() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\ud83d\\ude39\\ud83d\\udc8d\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_allowed_escapes() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\"\\\\/\b\f\n\r\t\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_backslash_and_u_escaped_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\\\u0000\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_backslash_doublequotes() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\"\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_comments() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"a/*b*/c/*d//e\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_double_escape_a() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\a\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_double_escape_n() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\n\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_escaped_control_character() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0012\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_escaped_noncharacter() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uFFFF\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_in_array() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"asd\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_in_array_with_leading_space() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"asd\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_last_surrogates_1_and_2() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uDBFF\\uDFFF\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_nbsp_uescaped() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"new\\u00A0line\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_nonCharacterInUTF_minus_8_U_plus_10FFFF() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"􏿿\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_nonCharacterInUTF_minus_8_U_plus_FFFF() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"￿\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_null_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0000\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_one_minus_byte_minus_utf_minus_8() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u002c\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_pi() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"π\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_reservedCharacterInUTF_minus_8_U_plus_1BFFF() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"𛿿\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_simple_ascii() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"asd \"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_space() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\" \"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD834\\uDd1e\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_three_minus_byte_minus_utf_minus_8() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0821\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_two_minus_byte_minus_utf_minus_8() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0123\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_u_plus_2028_line_sep() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\" \"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_u_plus_2029_par_sep() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\" \"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_uEscape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u0061\\u30af\\u30EA\\u30b9\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_uescaped_newline() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"new\\u000Aline\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unescaped_char_delete() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"⍂㈴⍂\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicodeEscapedBackslash() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u005C\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_2() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD83F\\uDFFE\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_10FFFE_nonchar() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uDBFF\\uDFFE\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_1FFFE_nonchar() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uDBFF\\uDFFE\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u200B\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_2064_invisible__plus_() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u2064\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_FDD0_nonchar() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uFDD0\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_U_plus_FFFE_nonchar() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uFFFE\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_unicode_escaped_double_quote() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u005C\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_utf8() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"€𝄞\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lexer_string_with_del_character() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"aa\"",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_STRING);
    ENSURE_STRING_EQ(token.lexeme, lexer.input);

    return OK;
}

int lex_lbrace() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_lbrace(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_rbrace() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "}",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_rbrace(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_lbracket() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_lbracket(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_rbracket() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "]",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_rbracket(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_colon() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ":",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_colon(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_comma() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ",",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_comma(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_string() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"poggers\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_eof() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_eof(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_number() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "12345",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_number(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_true() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "true",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_true(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_false() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "false",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_false(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int lex_null() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "null",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int main() {
    // Lex
    RUN_TEST(lex_lbrace);
    RUN_TEST(lex_rbrace);
    RUN_TEST(lex_lbracket);
    RUN_TEST(lex_rbracket);
    RUN_TEST(lex_colon);
    RUN_TEST(lex_comma);
    RUN_TEST(lex_string);
    RUN_TEST(lex_eof);
    RUN_TEST(lex_number);
    RUN_TEST(lex_true);
    RUN_TEST(lex_false);
    RUN_TEST(lex_null);

    // Simple tokens
    RUN_TEST(lexer_token_lbrace);
    RUN_TEST(lexer_token_rbrace);
    RUN_TEST(lexer_token_lbracket);
    RUN_TEST(lexer_token_rbracket);
    RUN_TEST(lexer_token_colon);
    RUN_TEST(lexer_token_comma);
    RUN_TEST(lexer_token_string);
    RUN_TEST(lexer_token_number);
    RUN_TEST(lexer_token_true);
    RUN_TEST(lexer_token_false);
    RUN_TEST(lexer_token_null);
    RUN_TEST(lexer_token_eof);

    // Number literals
    RUN_TEST(lexer_number_0eplus1);
    RUN_TEST(lexer_number_0e1);
    RUN_TEST(lexer_number_after_space);
    RUN_TEST(lexer_number_double_close_to_zero);
    RUN_TEST(lexer_number_int_with_exp);
    RUN_TEST(lexer_number_minus_zero);
    RUN_TEST(lexer_number_negative_int);
    RUN_TEST(lexer_number_negative_one);
    RUN_TEST(lexer_number_negative_zero);
    RUN_TEST(lexer_number_real_capital_e_neg_exp);
    RUN_TEST(lexer_number_real_capital_e_pos_exp);
    RUN_TEST(lexer_number_real_capital_e);
    RUN_TEST(lexer_number_real_exponent);
    RUN_TEST(lexer_number_real_fraction_exponent);
    RUN_TEST(lexer_number_real_neg_exp);
    RUN_TEST(lexer_number_real_pos_exponent);
    RUN_TEST(lexer_number_simple_int);
    RUN_TEST(lexer_number_simple_real);
    RUN_TEST(lexer_number);

    // String literals
    RUN_TEST(lexer_string_1_2_3_bytes_UTF_minus_8_sequences);
    RUN_TEST(lexer_string_accepted_surrogate_pair);
    RUN_TEST(lexer_string_accepted_surrogate_pairs);
    RUN_TEST(lexer_string_allowed_escapes);
    RUN_TEST(lexer_string_backslash_and_u_escaped_zero);
    RUN_TEST(lexer_string_backslash_doublequotes);
    RUN_TEST(lexer_string_comments);
    RUN_TEST(lexer_string_double_escape_a);
    RUN_TEST(lexer_string_double_escape_n);
    RUN_TEST(lexer_string_escaped_control_character);
    RUN_TEST(lexer_string_escaped_noncharacter);
    RUN_TEST(lexer_string_in_array);
    RUN_TEST(lexer_string_in_array_with_leading_space);
    RUN_TEST(lexer_string_last_surrogates_1_and_2);
    RUN_TEST(lexer_string_nbsp_uescaped);
    RUN_TEST(lexer_string_nonCharacterInUTF_minus_8_U_plus_10FFFF);
    RUN_TEST(lexer_string_nonCharacterInUTF_minus_8_U_plus_FFFF);
    RUN_TEST(lexer_string_null_escape);
    RUN_TEST(lexer_string_one_minus_byte_minus_utf_minus_8);
    RUN_TEST(lexer_string_pi);
    RUN_TEST(lexer_string_reservedCharacterInUTF_minus_8_U_plus_1BFFF);
    RUN_TEST(lexer_string_simple_ascii);
    RUN_TEST(lexer_string_space);
    RUN_TEST(lexer_string_surrogates_U_plus_1D11E_MUSICAL_SYMBOL_G_CLEF);
    RUN_TEST(lexer_string_three_minus_byte_minus_utf_minus_8);
    RUN_TEST(lexer_string_two_minus_byte_minus_utf_minus_8);
    RUN_TEST(lexer_string_u_plus_2028_line_sep);
    RUN_TEST(lexer_string_u_plus_2029_par_sep);
    RUN_TEST(lexer_string_uEscape);
    RUN_TEST(lexer_string_uescaped_newline);
    RUN_TEST(lexer_string_unescaped_char_delete);
    RUN_TEST(lexer_string_unicode);
    RUN_TEST(lexer_string_unicodeEscapedBackslash);
    RUN_TEST(lexer_string_unicode_2);
    RUN_TEST(lexer_string_unicode_U_plus_10FFFE_nonchar);
    RUN_TEST(lexer_string_unicode_U_plus_1FFFE_nonchar);
    RUN_TEST(lexer_string_unicode_U_plus_200B_ZERO_WIDTH_SPACE);
    RUN_TEST(lexer_string_unicode_U_plus_2064_invisible__plus_);
    RUN_TEST(lexer_string_unicode_U_plus_FDD0_nonchar);
    RUN_TEST(lexer_string_unicode_U_plus_FFFE_nonchar);
    RUN_TEST(lexer_string_unicode_escaped_double_quote);
    RUN_TEST(lexer_string_utf8);
    RUN_TEST(lexer_string_with_del_character);

    return 0;
}