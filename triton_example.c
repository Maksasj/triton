#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "triton.h"

int main() {
    const char *string = "[ true, false, \"poggers\" ]";

    triton_json_t json;
    if(triton_parse_json(&json, string).code == TRITON_OK) 
        printf("Parsed json\n");
    else
        printf("Failed to parse json\n");

    triton_stringify_json(stdout, &json);

    return 0;
}