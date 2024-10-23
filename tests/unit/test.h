#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <string.h>

#define FAIL 0
#define OK 1

#define RUN_TEST(TEST) printf("%-10s %-50s %-10s\n", "Running test", "'"#TEST"'", (TEST() ? "\x1B[32mSucceed\x1B[0m" : "\x1B[31mFailed\x1B[0m"));

#define ENSURE_EQ(A, B) if((A) != (B)) return FAIL
#define ENSURE_STRING_EQ(A, B) if(strcmp((A), (B)) != 0) return FAIL

#endif