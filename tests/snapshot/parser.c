#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

int main(int argc, char *argv[]) {
    FILE *stream = stdin;

    if(argc >= 2)
        stream = fopen(argv[1], "r");
    else 
        fprintf(stderr, "ERROR");

    triton_json_t json;

    // if(triton_parse(&json, stream).code = TRITON_ERROR) {
    //     printf("Failed to parse");
    // } else {
    //     printf("Parse succeeded");
    // }

    // triton_free_json(&json);

    return 0;
}