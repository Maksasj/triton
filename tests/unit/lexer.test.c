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
    ENSURE_STRING_EQ(token.lexeme, "4");

    return OK;
}

int lexer_number_before_space() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "4 ",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, "4");

    return OK;
}

int lexer_number_single_digit() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1",
        .pointer = 0
    };

    triton_token_t token = triton_next_token(&lexer);

    ENSURE_EQ(token.type, TRITON_TOKEN_NUMBER);
    ENSURE_STRING_EQ(token.lexeme, "1");

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

int lexer_string_unicode_U_plus_2064_invisible__plus() {
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

int lex_reject_number_hex_1_digit() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0x1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_1_dot_0e_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.0e+",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_with_alpha_char() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.8011670033376514H-308",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_2_dot_e3() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "2.e3",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_dot_2e_minus_3() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ".2e-3",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_bigger_minus_int() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "123�",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_real_without_fractional_part() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_expression() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1+2",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_dot_1_dot_2() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0.1.2",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_1_000() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1 000.0",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_starting_with_dot() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ".123",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_1_dot_0e_minus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.0e-",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_U_plus_FF11_fullwidth_digit_one() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "１",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_plus_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "++1234",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_infinity() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-Infinity",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_2_dot() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-2.",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_real_garbage_after_e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1ea",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_NaN() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "NaN",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_neg_real_without_int_part() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-.123",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_dot_3e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0.3e",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_space_1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "- 1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_exponent() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1e1�",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_sign_with_trailing_garbage() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-foo",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_invalid_plus_minus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0e+-1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_dot_3e_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0.3e+",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_9_dot_e_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "9.e+",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_dot_minus_1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = ".-1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_capital_E_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0E+",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_plus_Inf() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "+Inf",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_Inf() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "Inf",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_plus_1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "+1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_hex_2_digits() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0x42",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0e",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_infinity() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "Infinity",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_neg_int_starting_with_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-012",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_real_with_invalid_utf8_after_e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1e�",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_dot_e1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0.e1",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_neg_with_garbage_at_end() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-1x",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_1_dot_0e() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.0e",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_2_dot_e_minus_3() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "2.e-3",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0e_plus() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0e+",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_01() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-01",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_1_dot_0_dot() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-1.0.",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_int() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0�",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_with_leading_zero() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "012",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_2_dot_e_plus_3() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "2.e+3",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_1eE2() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1eE2",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_0_capital_E() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "0E",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_with_alpha() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1.2a-3",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_minus_NaN() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-NaN",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_number_invalid_minus_negative_minus_real() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "-123.123foo",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_null(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int lex_reject_string_unescaped_newline() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"new\nline\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_backslash_00() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_incomplete_surrogate_escape_invalid() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD800\\uD800\\x\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_1_surrogate_then_escape_u1() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD800\\u1\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_invalid_unicode_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uqqqq\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_single_doublequote() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_invalid_utf_8_in_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u�\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_1_surrogate_then_escape_u() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD800\\u\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_accentuated_char_no_quotes() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "é",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_incomplete_surrogate() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD834\\uDd\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_1_surrogate_then_escape_u1x() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD800\\u1x\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_invalid_utf8_after_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\�\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_single_string_no_double_quotes() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "abc",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_unescaped_ctrl_char() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"aa\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_escaped_backslash_bad() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\\\\\\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_unescaped_tab() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"      \"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_single_quote() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "'single quote'",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_incomplete_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_escaped_emoji() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\🌀\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_invalid_backslash_esc() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\a\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_1_surrogate_then_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\uD800\\\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_escaped_ctrl_char_tab() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\     \"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_escape_x() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\x00\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_unicode_CapitalU() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\\UA66D",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_no_quotes_with_bad_escape() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\\n",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_leading_uescaped_thinspace() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\\u0020\"asd\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_with_trailing_garbage() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\"x",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_start_escape_unclosed() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}

int lex_reject_string_incomplete_escaped_character() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"\\u00A\"",
        .pointer = 0
    };

    triton_token_t token;
    triton_lex_result_t result = triton_lex_string(&token, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK; 
}


int lex_simple_group() {
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

    return OK;
}

int lex_tokens_group() {
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

    return OK;
}

int lex_number_literals_accepted_group() {
    // Number literals
    RUN_TEST(lexer_number_0eplus1);
    RUN_TEST(lexer_number_0e1);
    RUN_TEST(lexer_number_after_space);
    RUN_TEST(lexer_number_before_space);
    RUN_TEST(lexer_number_single_digit);
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

    return OK;
}

int lex_number_literals_rejected_group() {
    RUN_TEST(lex_reject_number_hex_1_digit);
    RUN_TEST(lex_reject_number_1_dot_0e_plus);
    RUN_TEST(lex_reject_number_with_alpha_char);
    RUN_TEST(lex_reject_number_2_dot_e3);
    RUN_TEST(lex_reject_number_dot_2e_minus_3);
    RUN_TEST(lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_bigger_minus_int);
    RUN_TEST(lex_reject_number_real_without_fractional_part);
    RUN_TEST(lex_reject_number_expression);
    RUN_TEST(lex_reject_number_0_dot_1_dot_2);
    RUN_TEST(lex_reject_number_1_000);
    RUN_TEST(lex_reject_number_starting_with_dot);
    RUN_TEST(lex_reject_number_1_dot_0e_minus);
    RUN_TEST(lex_reject_number_U_plus_FF11_fullwidth_digit_one);
    RUN_TEST(lex_reject_number_plus_plus);
    RUN_TEST(lex_reject_number_minus_infinity);
    RUN_TEST(lex_reject_number_minus_2_dot);
    RUN_TEST(lex_reject_number_real_garbage_after_e);
    RUN_TEST(lex_reject_number_NaN);
    RUN_TEST(lex_reject_number_neg_real_without_int_part);
    RUN_TEST(lex_reject_number_0_dot_3e);
    RUN_TEST(lex_reject_number_minus_space_1);
    RUN_TEST(lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_exponent);
    RUN_TEST(lex_reject_number_minus_sign_with_trailing_garbage);
    RUN_TEST(lex_reject_number_invalid_plus_minus);
    RUN_TEST(lex_reject_number_0_dot_3e_plus);
    RUN_TEST(lex_reject_number_9_dot_e_plus);
    RUN_TEST(lex_reject_number_dot_minus_1);
    RUN_TEST(lex_reject_number_0_capital_E_plus);
    RUN_TEST(lex_reject_number_plus_Inf);
    RUN_TEST(lex_reject_number_Inf);
    RUN_TEST(lex_reject_number_plus_1);
    RUN_TEST(lex_reject_number_hex_2_digits);
    RUN_TEST(lex_reject_number_0e);
    RUN_TEST(lex_reject_number_infinity);
    RUN_TEST(lex_reject_number_neg_int_starting_with_zero);
    RUN_TEST(lex_reject_number_real_with_invalid_utf8_after_e);
    RUN_TEST(lex_reject_number_0_dot_e1);
    RUN_TEST(lex_reject_number_neg_with_garbage_at_end);
    RUN_TEST(lex_reject_number_1_dot_0e);
    RUN_TEST(lex_reject_number_2_dot_e_minus_3);
    RUN_TEST(lex_reject_number_0e_plus);
    RUN_TEST(lex_reject_number_minus_01);
    RUN_TEST(lex_reject_number_minus_1_dot_0_dot);
    RUN_TEST(lex_reject_number_invalid_minus_utf_minus_8_minus_in_minus_int);
    RUN_TEST(lex_reject_number_with_leading_zero);
    RUN_TEST(lex_reject_number_2_dot_e_plus_3);
    RUN_TEST(lex_reject_number_1eE2);
    RUN_TEST(lex_reject_number_0_capital_E);
    RUN_TEST(lex_reject_number_with_alpha);
    RUN_TEST(lex_reject_number_minus_NaN);
    RUN_TEST(lex_reject_number_invalid_minus_negative_minus_real);

    return OK;
}

int lex_number_literals_group() {
    RUN_TEST_GROUP(lex_number_literals_accepted_group);
    RUN_TEST_GROUP(lex_number_literals_rejected_group);

    return OK;
}

int lex_string_literals_accepted_group() {
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
    RUN_TEST(lexer_string_unicode_U_plus_2064_invisible__plus);
    RUN_TEST(lexer_string_unicode_U_plus_FDD0_nonchar);
    RUN_TEST(lexer_string_unicode_U_plus_FFFE_nonchar);
    RUN_TEST(lexer_string_unicode_escaped_double_quote);
    RUN_TEST(lexer_string_utf8);
    RUN_TEST(lexer_string_with_del_character);

    return OK;
}

int lex_string_literals_rejected_group() {
    RUN_TEST(lex_reject_string_unescaped_newline);
    RUN_TEST(lex_reject_string_backslash_00);
    RUN_TEST(lex_reject_string_incomplete_surrogate_escape_invalid);
    RUN_TEST(lex_reject_string_1_surrogate_then_escape_u1);
    RUN_TEST(lex_reject_string_invalid_unicode_escape);
    RUN_TEST(lex_reject_string_single_doublequote);
    RUN_TEST(lex_reject_string_invalid_utf_8_in_escape);
    RUN_TEST(lex_reject_string_1_surrogate_then_escape_u);
    RUN_TEST(lex_reject_string_accentuated_char_no_quotes);
    RUN_TEST(lex_reject_string_incomplete_surrogate);
    RUN_TEST(lex_reject_string_1_surrogate_then_escape_u1x);
    RUN_TEST(lex_reject_string_invalid_utf8_after_escape);
    RUN_TEST(lex_reject_string_single_string_no_double_quotes);
    RUN_TEST(lex_reject_string_unescaped_ctrl_char);
    RUN_TEST(lex_reject_string_escaped_backslash_bad);
    RUN_TEST(lex_reject_string_unescaped_tab);
    RUN_TEST(lex_reject_string_single_quote);
    RUN_TEST(lex_reject_string_incomplete_escape);
    RUN_TEST(lex_reject_string_escaped_emoji);
    RUN_TEST(lex_reject_string_invalid_backslash_esc);
    RUN_TEST(lex_reject_string_1_surrogate_then_escape);
    RUN_TEST(lex_reject_string_escaped_ctrl_char_tab);
    RUN_TEST(lex_reject_string_escape_x);
    RUN_TEST(lex_reject_string_unicode_CapitalU);
    RUN_TEST(lex_reject_string_no_quotes_with_bad_escape);
    RUN_TEST(lex_reject_string_leading_uescaped_thinspace);
    RUN_TEST(lex_reject_string_with_trailing_garbage);
    RUN_TEST(lex_reject_string_start_escape_unclosed);
    RUN_TEST(lex_reject_string_incomplete_escaped_character);

    return OK;
}

int lex_string_literals_group() {
    RUN_TEST_GROUP(lex_string_literals_accepted_group);
    RUN_TEST_GROUP(lex_string_literals_rejected_group);

    return OK;
}

int main() {
    RUN_TEST_GROUP(lex_simple_group);
    RUN_TEST_GROUP(lex_tokens_group);
    RUN_TEST_GROUP(lex_number_literals_group);
    RUN_TEST_GROUP(lex_string_literals_group);
   
    return 0;
}