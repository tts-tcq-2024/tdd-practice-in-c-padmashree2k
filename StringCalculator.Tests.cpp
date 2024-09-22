#include <assert.h>
#include <stdio.h>
#include "StringCalculator.h"

void test_empty_string() {
    assert(add("") == 0);
    printf("Test empty string passed\n");
}

void test_single_number() {
    assert(add("1") == 1);
    printf("Test single number passed\n");
}

void test_two_numbers() {
    assert(add("1,2") == 3);
    printf("Test two numbers passed\n");
}

void test_multiple_numbers() {
    assert(add("1,2,3,4") == 10);
    printf("Test multiple numbers passed\n");
}

void test_newline_and_comma() {
    assert(add("1\n2,3") == 6);
    printf("Test newline and comma passed\n");
}

void test_custom_delimiter() {
    assert(add("//;\n1;2") == 3);
    printf("Test custom delimiter passed\n");
}

void test_ignore_large_numbers() {
    assert(add("2,1001") == 2);
    printf("Test ignore large numbers passed\n");
}

void test_negative_numbers() {
    printf("Running negative number test...\n");
    int result = add("-1,-2,3");
    assert(result == -1);  // Expect error code -1 for negative numbers
    printf("Test negative numbers passed\n");
}

int main() {
    test_empty_string();
    test_single_number();
    test_two_numbers();
    test_multiple_numbers();
    test_newline_and_comma();
    test_custom_delimiter();
    test_ignore_large_numbers();
    test_negative_numbers();

    printf("All tests passed\n");
    return 0;
}
