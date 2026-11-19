// test.h
#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int tests_run = 0;
static int tests_passed = 0;

#define PRINT_FAIL(desc, expected, got) \
    printf("FAIL: %s\n", desc); \
    printf("  Expected: '%s'\n", expected); \
    printf("  Got:      '%s'\n", got);

#define ASSERT_STR_EQ(desc, expected, got) { \
    tests_run++; \
    if (strcmp(expected, got) == 0) { \
        tests_passed++; \
    } else { \
        PRINT_FAIL(desc, expected, got); \
    } \
}

#define ASSERT_INT_EQ(desc, expected, got) { \
    tests_run++; \
    if (expected == got) { \
        tests_passed++; \
    } else { \
        printf("FAIL: %s\n", desc); \
        printf("  Expected: %d\n", expected); \
        printf("  Got:      %d\n", got); \
    } \
}

#define RUN_TEST(func) func();

#endif