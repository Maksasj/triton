#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

#define FAIL 0
#define OK 1

typedef int (*test_case_t)();

void run_test(const char* test_name, test_case_t test_case) {
    int result = (*test_case)();

    printf("%-10s %-100s %-10s\n", "Running test", test_name, (result ? "\x1B[32mSucceed\x1B[0m" : "\x1B[31mFailed\x1B[0m"));
}

void run_test_group(test_case_t test_case) {
    printf("%s\n", "Running test group");

    int result = (*test_case)();
}

#define RUN_TEST(TEST) run_test(#TEST, &(TEST));

#define RUN_TEST_GROUP(GROUP) run_test_group(&(GROUP))

#define ENSURE_EQ(A, B) if((A) != (B)) return FAIL
#define ENSURE_STRING_EQ(A, B) if(strcmp((A), (B)) != 0) return FAIL

#endif