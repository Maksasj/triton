#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "../../triton.h"

int main(int argc, char *argv[]) {
    FILE *stream = stdin;

    if(argc >= 2)
        stream = fopen(argv[1], "r");
    else {
        fprintf(stderr, "ERROR");
        return 1;
    }

    char* buffer = 0;
    long length;

    fseek (stream, 0, SEEK_END);
    length = ftell(stream);
    fseek (stream, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer == NULL) {
    fprintf(stderr, "ERROR");
        return 1;
    }

    fread(buffer, 1, length, stream);

    triton_json_t json;
    triton_parse_result_t result = triton_parse_json(&json, buffer);

    if(result.code == TRITON_ERROR) {
        printf("Failed to parse");
    } else {
        triton_stringify_json(stdout, &json);
    }

    fclose (stream);

    return 0;
}