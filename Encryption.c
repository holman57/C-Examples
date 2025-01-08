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

/*
 * Complete the 'encryption' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

/*
 * To return the string from the function, you should either do static allocation or dynamic allocation
 *
 * For example,
 * char* return_string_using_static_allocation() {
 *     static char s[] = "static allocation of string";
 *
 *     return s;
 * }
 *
 * char* return_string_using_dynamic_allocation() {
 *     char* s = malloc(100 * sizeof(char));
 *
 *     s = "dynamic allocation of string";
 *
 *     return s;
 * }
 *
 */

char* encryption(char* s) {
    // Step 1: Remove spaces from the input string
    int len = strlen(s);
    char* cleaned = malloc(len + 1);
    int cleaned_len = 0;

    for (int i = 0; i < len; ++i) {
        if (s[i] != ' ') {
            cleaned[cleaned_len++] = s[i];
        }
    }
    cleaned[cleaned_len] = '\0';

    // Step 2: Determine the number of rows and columns
    int L = cleaned_len;
    int rows = floor(sqrt(L));
    int columns = ceil(sqrt(L));
    if (rows * columns < L) {
        rows++;
    }

    // Step 3: Create the encrypted string column by column
    char* encrypted = malloc(L + columns + 1); // Allocating enough space for the result
    int pos = 0;
    for (int col = 0; col < columns; ++col) {
        for (int row = 0; row < rows; ++row) {
            int index = row * columns + col;
            if (index < L) {
                encrypted[pos++] = cleaned[index];
            }
        }
        encrypted[pos++] = ' '; // Space after each column group
    }
    encrypted[pos - 1] = '\0'; // Replace the last space with a null terminator

    free(cleaned);
    return encrypted;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = encryption(s);

    fprintf(fptr, "%s\n", result);

    fclose(fptr);

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

