#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

void kaprekarNumbers(int p, int q) {
    int found = 0; // To track if we find any Kaprekar number

    for (int i = p; i <= q; i++) {
        long square = (long)i * i; // Compute the square of the number
        char square_str[20]; // To hold the square as string
        sprintf(square_str, "%ld", square); // Convert square to string
        int len = strlen(square_str); // Total number of digits in the square

        char left_part[20] = {0}, right_part[20] = {0};
        int split_pos = len - (int)log10(i) - 1; // Calculate split position

        // Split the string
        strncpy(left_part, square_str, split_pos); // Left part
        strcpy(right_part, square_str + split_pos); // Right part

        // Convert parts to integers
        long left_num = (left_part[0] != '\0') ? atol(left_part) : 0;
        long right_num = atol(right_part);

        // Sum the parts and check if it equals the original number
        if ((left_num + right_num) == i) {
            printf("%d ", i);
            found = 1;
        }
    }

    if (!found) {
        printf("INVALID RANGE");
    }

    printf("\n"); // End the output with a newline
}

int main()
{
    int p = parse_int(ltrim(rtrim(readline())));

    int q = parse_int(ltrim(rtrim(readline())));

    kaprekarNumbers(p, q);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
