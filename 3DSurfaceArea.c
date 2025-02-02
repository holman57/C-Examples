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
char** split_string(char*);

int parse_int(char*);

/*
 * Complete the 'surfaceArea' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts 2D_INTEGER_ARRAY A as parameter.
 */

int surfaceArea(int A_rows, int A_columns, int** A) {
    int surfaceArea = 0;

    // Iterate through each cell in the grid
    for (int i = 0; i < A_rows; i++) {
        for (int j = 0; j < A_columns; j++) {
            int height = A[i][j];

            // Add top and bottom faces of the current stack
            surfaceArea += 2; // Top and Bottom

            // Check all four neighbors (up, down, left, right)

            // Up
            if (i == 0) {
                // If at the top edge, add full height
                surfaceArea += height;
            } else {
                // Otherwise, add the difference
                surfaceArea += (height > A[i - 1][j]) ? (height - A[i - 1][j]) : 0;
            }

            // Down
            if (i == A_rows - 1) {
                // If at the bottom edge, add full height
                surfaceArea += height;
            } else {
                // Otherwise, add the difference
                surfaceArea += (height > A[i + 1][j]) ? (height - A[i + 1][j]) : 0;
            }

            // Left
            if (j == 0) {
                // If at the left edge, add full height
                surfaceArea += height;
            } else {
                // Otherwise, add the difference
                surfaceArea += (height > A[i][j - 1]) ? (height - A[i][j - 1]) : 0;
            }

            // Right
            if (j == A_columns - 1) {
                // If at the right edge, add full height
                surfaceArea += height;
            } else {
                // Otherwise, add the difference
                surfaceArea += (height > A[i][j + 1]) ? (height - A[i][j + 1]) : 0;
            }
        }
    }

    return surfaceArea;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int H = parse_int(*(first_multiple_input + 0));

    int W = parse_int(*(first_multiple_input + 1));

    int** A = malloc(H * sizeof(int*));

    for (int i = 0; i < H; i++) {
        *(A + i) = malloc(W * (sizeof(int)));

        char** A_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < W; j++) {
            int A_item = parse_int(*(A_item_temp + j));

            *(*(A + i) + j) = A_item;
        }
    }

    int result = surfaceArea(H, W, A);

    fprintf(fptr, "%d\n", result);

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
