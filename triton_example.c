#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "triton.h"

int main() {
    Triton tri = {
        .sink = stdout
    };

    tri_begin_object(&tri);
        tri_member_key(&tri, "object");
        tri_begin_object(&tri);
            tri_member_key(&tri, "one");
            tri_bool(&tri, 0);
            tri_member_key(&tri, "two");
            tri_bool(&tri, 0);
            tri_member_key(&tri, "three");
            tri_bool(&tri, 0);
        tri_object_end(&tri);

        tri_member_key(&tri, "array");
        tri_begin_array(&tri);
        for(int i = 0; i < 5; ++i) {
            tri_integer(&tri, i);
        } 
        tri_array_end(&tri);
    tri_object_end(&tri);

    return 0;
}