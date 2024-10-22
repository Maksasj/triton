#define TRITON_IMPLEMENTATION
#include "triton.h"

int main() {
    Triton tri = {

    };

    tri_object_begin(&tri);
        tri_member_key(&tri, "null");
        tri_null(&tri);

        tri_member_key(&tri, "bool");
        // tri_array_begin(&tri);
        //     tri_bool(&tri, 0);
        //     tri_bool(&tri, 1);
        // tri_array_end(&tri);

        tri_member_key(&tri, "integers");
        // tri_array_begin(&tri);
        //     for (int i = -3; i <= 3; ++i) {
        //         tri_integer(&tri, i);
        //     }
        // tri_array_end(&tri);

        tri_member_key(&tri, "floats");
        // tri_array_begin(&tri);
        //     tri_float(&tri, 0.0, 4);
        //     tri_float(&tri, -0.0, 4);
        //     tri_float(&tri, 3.1415, 4);
        //     tri_float(&tri, 2.71828, 5);
        //     tri_float(&tri, 1.6180, 4);
        //     tri_float(&tri, 0.0 / 0.0, 4);
        //     tri_float(&tri, 1.0 / 0.0, 4);
        //     tri_float(&tri, -1.0 / 0.0, 4);
        // tri_array_end(&tri);

        tri_member_key(&tri, "string");
        // tri_array_begin(&tri);
        //     tri_string(&tri, "Hello\tWorld\n");
        //     tri_string_sized(&tri, "\0\0\0\0", 4);
        // tri_array_end(&tri);
    tri_object_end(&tri);

    return 0;
}