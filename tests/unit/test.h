#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define RUN_TEST(TEST) printf("Running test '%s': ", #TEST); if((TEST())) printf("Succeed\n"); else printf("Failed\n");
#define ENSURE_EQ(A, B) ((A) == (B))
#define FAIL 0
#define OK 1

#endif