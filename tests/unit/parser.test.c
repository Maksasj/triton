#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

#include "test.h"

int parse_string() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "\"some string\"",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_string(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_PRIMITIVE_VALUE);

    return OK;
}

int parse_number() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "1235",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_number(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_PRIMITIVE_VALUE);

    return OK;
}

int parse_object_empty() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_OBJECT_VALUE);
    ENSURE_EQ(value.as.array.count, 0);

    return OK;
}

int parse_object_single_element() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ \"key\": true }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_OBJECT_VALUE);
    ENSURE_EQ(value.as.object.count, 1);

    return OK;
}

int parse_object_two_elements() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ \"key\": true, \"key1\": false }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_OBJECT_VALUE);
    ENSURE_EQ(value.as.object.count, 2);

    return OK;
}

int parse_array_empty() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 0);

    return OK;
}

int parse_array_single_element() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ true ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 1);

    return OK;
}

int parse_array_with_array() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ [ ] ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 1);

    return OK;
}

int parse_array_with_arrays() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ [ ], [ ], [ [ ] ] ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 3);

    return OK;
}

int parse_array_two_elements() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ true, false ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 2);

    return OK;
}

int parse_array_with_values_odd_items() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ true, \"some string\", 1234, null, \"another string\" ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 5);

    return OK;
}

int parse_array_with_values_even_items() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ true, \"some string\", 1234, null ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 4);

    return OK;
}

int parse_true() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "true",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_true(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_PRIMITIVE_VALUE);

    return OK;
}

int parse_false() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "false",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_false(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_PRIMITIVE_VALUE);

    return OK;
}

int parse_null() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "null",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_null(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_PRIMITIVE_VALUE);
    
    return OK;
}

int main() {
    // Simple tokens
    RUN_TEST(parse_string);
    RUN_TEST(parse_number);
    
    RUN_TEST(parse_object_empty);
    RUN_TEST(parse_object_single_element);
    RUN_TEST(parse_object_two_elements);
    
    RUN_TEST(parse_array_empty);
    RUN_TEST(parse_array_single_element);
    RUN_TEST(parse_array_with_array);
    RUN_TEST(parse_array_with_arrays);
    RUN_TEST(parse_array_two_elements);
    RUN_TEST(parse_array_with_values_odd_items);
    RUN_TEST(parse_array_with_values_even_items);

    RUN_TEST(parse_true);
    RUN_TEST(parse_false);
    RUN_TEST(parse_null);

    return 0;
}