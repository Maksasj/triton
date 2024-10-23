#define TRITON_IMPLEMENTATION
#include "../triton.h"

int main(int argc, char *argv[]) {
    FILE *stream = stdin;

    if(argc >= 2)
        stream = fopen(argv[1], "r");
    else 
        fprintf(stderr, "ERROR");

    printf("Parsing %s!\n", argv[1]);

    // Todo parse

    return 0;
}