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

/*
 * Complete the 'bigSorting' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY unsorted as parameter.
 */

/*
 * To return the string array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * char** return_string_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static char* a[5] = {"static", "allocation", "of", "string", "array"};
 *
 *     return a;
 * }
 *
 * char** return_string_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     char** a = malloc(5 * sizeof(char*));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = malloc(20 * sizeof(char));
 *     }
 *
 *     *(a + 0) = "dynamic";
 *     *(a + 1) = "allocation";
 *     *(a + 2) = "of";
 *     *(a + 3) = "string";
 *     *(a + 4) = "array";
 *
 *     return a;
 * }
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;

    // Compare based on length first
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    if (len1 < len2) {
        return -1;
    } else if (len1 > len2) {
        return 1;
    }

    // If lengths are equal, compare lexicographically
    return strcmp(str1, str2);
}

char** bigSorting(int unsorted_count, char** unsorted, int* result_count) {
    // Sort the array using qsort with the custom comparator
    qsort(unsorted, unsorted_count, sizeof(char*), compare);

    // Set the result count to the number of elements
    *result_count = unsorted_count;

    // Return the sorted array
    return unsorted;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** unsorted = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* unsorted_item = readline();

        *(unsorted + i) = unsorted_item;
    }

    int result_count;
    char** result = bigSorting(n, unsorted, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
