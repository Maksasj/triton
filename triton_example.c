#include <stdio.h>

#define TRITON_IMPLEMENTATION
#include "triton.h"

int main() {
    triser_t tri = {
        .sink = stdout
    };

    /*
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
        tri_end_array(&tri);

        tri_member_key(&tri, "another");
        tri_begin_array(&tri);
        for(int i = 0; i < 5; ++i) {
            tri_integer(&tri, i);
        } 
        tri_end_array(&tri);
    tri_object_end(&tri);
    */
   
    tri_begin_object(&tri);
        tri_member_key(&tri, "name");
        tri_string(&tri, "Sample Object");

        tri_member_key(&tri, "version");
        tri_float(&tri, 1.0);

        tri_member_key(&tri, "active");
        tri_bool(&tri, 1);

        tri_member_key(&tri, "nullValue");
        tri_null(&tri);

        tri_member_key(&tri, "attributes");
        tri_begin_object(&tri);
            tri_member_key(&tri, "height");
            tri_integer(&tri, 180);

            tri_member_key(&tri, "weight");
            tri_float(&tri, 75.5f);

            tri_member_key(&tri, "preferences");
            tri_begin_object(&tri);
                tri_member_key(&tri, "colors");
                tri_begin_array(&tri);
                    tri_string(&tri, "red");
                    tri_string(&tri, "green");
                    tri_string(&tri, "blue");
                tri_end_array(&tri);

                tri_member_key(&tri, "languages");
                tri_begin_array(&tri);
                    tri_begin_object(&tri);
                        tri_member_key(&tri, "name");
                        tri_string(&tri, "English");

                        tri_member_key(&tri, "level");
                        tri_string(&tri, "fluent");
                    tri_object_end(&tri);
                    tri_begin_object(&tri);
                        tri_member_key(&tri, "name");
                        tri_string(&tri, "Japanese");

                        tri_member_key(&tri, "level");
                        tri_string(&tri, "intermediate");
                    tri_object_end(&tri);
                tri_end_array(&tri);
            tri_object_end(&tri);
        tri_object_end(&tri);
        tri_member_key(&tri, "tags");
        tri_begin_array(&tri);
            tri_string(&tri, "sample");
            tri_string(&tri, "json");
            tri_string(&tri, "test");
        tri_end_array(&tri);
        tri_member_key(&tri, "metadata");
        tri_begin_array(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "key");
                tri_string(&tri, "author");

                tri_member_key(&tri, "value");
                tri_string(&tri, "John Doe");
            tri_object_end(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "key");
                tri_string(&tri, "date_created");

                tri_member_key(&tri, "value");
                tri_string(&tri, "2024-10-22");
            tri_object_end(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "key");
                tri_string(&tri, "category");

                tri_member_key(&tri, "value");
                tri_string(&tri, "example");
            tri_object_end(&tri);
        tri_end_array(&tri);
        tri_member_key(&tri, "validations");
        tri_begin_array(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "field");
                tri_string(&tri, "name");

                tri_member_key(&tri, "value");
                tri_bool(&tri, 1);
            tri_object_end(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "field");
                tri_string(&tri, "date_created");

                tri_member_key(&tri, "value");
                tri_bool(&tri, 1);
            tri_object_end(&tri);
            tri_begin_object(&tri);
                tri_member_key(&tri, "field");
                tri_string(&tri, "tags");

                tri_member_key(&tri, "value");
                tri_bool(&tri, 0);
            tri_object_end(&tri);
        tri_end_array(&tri);
    tri_object_end(&tri);

    return 0;
}