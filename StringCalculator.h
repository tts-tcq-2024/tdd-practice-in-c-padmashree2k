#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <setjmp.h>

#define MAX_DELIMITER_LEN 10

jmp_buf jump_buffer;  // For handling negative number errors

// Helper function to check if a character is a digit
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Helper function to extract the delimiter from the string
const char* extract_delimiter(const char* str, char* delimiter) {
    if (str[0] == '/' && str[1] == '/') {
        const char* newline_pos = strchr(str, '\n');
        if (newline_pos) {
            size_t len = newline_pos - str - 2;
            strncpy(delimiter, str + 2, len);
            delimiter[len] = '\0';
            return newline_pos + 1;  // Return pointer after the delimiter line
        }
    }
    strcpy(delimiter, ",");  // Default delimiter is comma
    return str;
}

// Function to split the string and return the sum
int add(const char* numbers) {
    if (strlen(numbers) == 0) {
        return 0;  // Empty string returns 0
    }

    char delimiter[MAX_DELIMITER_LEN];
    numbers = extract_delimiter(numbers, delimiter);  // Set custom or default delimiter

    int sum = 0;
    int negatives[10];
    int neg_count = 0;
    char buffer[100] = {0};  // Temporary buffer to hold current number
    int buffer_pos = 0;

    for (int i = 0; numbers[i] != '\0'; i++) {
        char current = numbers[i];

        if (is_digit(current)) {
            buffer[buffer_pos++] = current;  // Collect digits
        } else if (current == '\n' || strchr(delimiter, current)) {
            buffer[buffer_pos] = '\0';  // End current number
            if (buffer_pos > 0) {
                int num = atoi(buffer);
                if (num < 0) {
                    negatives[neg_count++] = num;  // Collect negative numbers
                } else if (num <= 1000) {
                    sum += num;  // Add to sum if <= 1000
                }
                buffer_pos = 0;
            }
        }
    }

    // Handle the last number if there is any
    if (buffer_pos > 0) {
        int num = atoi(buffer);
        if (num < 0) {
            negatives[neg_count++] = num;
        } else if (num <= 1000) {
            sum += num;
        }
    }

    // Check if there were any negative numbers
    if (neg_count > 0) {
        printf("negatives not allowed: ");
        for (int i = 0; i < neg_count; i++) {
            printf("%d ", negatives[i]);
        }
        printf("\n");
        longjmp(jump_buffer, 1);  // Use longjmp to exit gracefully
    }

    return sum;
}
