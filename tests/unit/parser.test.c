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

int parse_object_number_invalid_key() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ \"key\": true, 11: false }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int parse_object_object_invalid_key() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ \"key\": true, { \"key\": true }: false }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int parse_object_recursive_object() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "{ \"key\": { \"key\": { \"key\": { \"key\": { } } } } }",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_object(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_OBJECT_VALUE);
    ENSURE_EQ(value.as.object.count, 1);

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

int parse_array_with_empty_objects() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ {}, {}, {}, {}, {}, {} ]",
        .pointer = 0
    };

    triton_value_t value;
    triton_parse_result_t result = triton_parse_array(&value, &lexer);

    ENSURE_EQ(result.code, TRITON_OK);
    ENSURE_EQ(value.type, TRITON_ARRAY_VALUE);
    ENSURE_EQ(value.as.array.count, 6);

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

int parse_array_with_numbers() {
    triton_lexer_t lexer = (triton_lexer_t) {
        .input = "[ 12344, 123.0, 1235.1, 0.0 ]",
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

int parse_json_with_string() {
    const char* input = "\"some string\"";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_number() {
    const char* input = "1235";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_object_empty() {
    const char* input = "{ }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_object_single_element() {
    const char* input = "{ \"key\": true }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_object_two_elements() {
    const char* input = "{ \"key\": true, \"key1\": false }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_object_number_invalid_key() {
    const char* input = "{ \"key\": true, 11: false }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int parse_json_with_object_object_invalid_key() {
    const char* input = "{ \"key\": true, { \"key\": true }: false }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_ERROR);

    return OK;
}

int parse_json_with_object_recursive_object() {
    const char* input = "{ \"key\": { \"key\": { \"key\": { \"key\": { } } } } }";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_empty() {
    const char* input = "[ ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_single_element() {
    const char* input = "[ true ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_with_array() {
    const char* input = "[ [ ] ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_with_empty_objects() {
    const char* input = "[ {}, {}, {}, {}, {}, {} ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_with_arrays() {
    const char* input = "[ [ ], [ ], [ [ ] ] ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_two_elements() {
    const char* input = "[ true, false ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_with_values_odd_items() {
    const char* input = "[ true, \"some string\", 1234, null, \"another string\" ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_array_with_values_even_items() {
    const char* input = "[ true, \"some string\", 1234, null ]";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_true() {
    const char* input = "true";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_false() {
    const char* input = "false";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);

    return OK;
}

int parse_json_with_null() {
    const char* input = "null";

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, input);

    ENSURE_EQ(result.code, TRITON_OK);
    
    return OK;
}

int main() {
    // simple tokens
    RUN_TEST(parse_string);
    RUN_TEST(parse_number);
    
    RUN_TEST(parse_object_empty);
    RUN_TEST(parse_object_single_element);
    RUN_TEST(parse_object_two_elements);
    RUN_TEST(parse_object_number_invalid_key);
    RUN_TEST(parse_object_object_invalid_key);
    RUN_TEST(parse_object_recursive_object);

    RUN_TEST(parse_array_empty);
    RUN_TEST(parse_array_single_element);
    RUN_TEST(parse_array_with_array);
    RUN_TEST(parse_array_with_empty_objects);
    RUN_TEST(parse_array_with_arrays);
    RUN_TEST(parse_array_two_elements);
    RUN_TEST(parse_array_with_values_odd_items);
    RUN_TEST(parse_array_with_values_even_items);
    RUN_TEST(parse_array_with_numbers);

    RUN_TEST(parse_true);
    RUN_TEST(parse_false);
    RUN_TEST(parse_null);

    // json
    RUN_TEST(parse_json_with_string);
    RUN_TEST(parse_json_with_number);
    
    RUN_TEST(parse_json_with_object_empty);
    RUN_TEST(parse_json_with_object_single_element);
    RUN_TEST(parse_json_with_object_two_elements);
    RUN_TEST(parse_json_with_object_number_invalid_key);
    RUN_TEST(parse_json_with_object_object_invalid_key);
    RUN_TEST(parse_json_with_object_recursive_object);

    RUN_TEST(parse_json_with_array_empty);
    RUN_TEST(parse_json_with_array_single_element);
    RUN_TEST(parse_json_with_array_with_array);
    RUN_TEST(parse_json_with_array_with_empty_objects);
    RUN_TEST(parse_json_with_array_with_arrays);
    RUN_TEST(parse_json_with_array_two_elements);
    RUN_TEST(parse_json_with_array_with_values_odd_items);
    RUN_TEST(parse_json_with_array_with_values_even_items);

    RUN_TEST(parse_json_with_true);
    RUN_TEST(parse_json_with_false);
    RUN_TEST(parse_json_with_null);

    return 0;
}