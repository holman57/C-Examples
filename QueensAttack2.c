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
 * Complete the 'queensAttack' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER k
 *  3. INTEGER r_q
 *  4. INTEGER c_q
 *  5. 2D_INTEGER_ARRAY obstacles
 */

int queensAttack(int n, int k, int r_q, int c_q, int obstacles_rows, int obstacles_columns, int** obstacles) {
    // Initialize movement limits in 8 directions
    int up = n - r_q;
    int down = r_q - 1;
    int left = c_q - 1;
    int right = n - c_q;

    int top_left = (r_q - 1 < c_q - 1) ? r_q - 1 : c_q - 1;
    int top_right = (r_q - 1 < n - c_q) ? r_q - 1 : n - c_q;
    int bottom_left = (n - r_q < c_q - 1) ? n - r_q : c_q - 1;
    int bottom_right = (n - r_q < n - c_q) ? n - r_q : n - c_q;

    // Process each obstacle
    for (int i = 0; i < k; i++) {
        int obs_row = obstacles[i][0];
        int obs_col = obstacles[i][1];

        // Check if obstacle affects the column (up or down)
        if (obs_col == c_q) {
            if (obs_row > r_q) {
                up = (obs_row - r_q - 1 < up) ? obs_row - r_q - 1 : up;
            } else {
                down = (r_q - obs_row - 1 < down) ? r_q - obs_row - 1 : down;
            }
        }
        // Check if obstacle affects the row (left or right)
        else if (obs_row == r_q) {
            if (obs_col > c_q) {
                right = (obs_col - c_q - 1 < right) ? obs_col - c_q - 1 : right;
            } else {
                left = (c_q - obs_col - 1 < left) ? c_q - obs_col - 1 : left;
            }
        }
        // Check if obstacle affects diagonals
        else if (abs(obs_row - r_q) == abs(obs_col - c_q)) {
            // Top-left diagonal
            if (obs_row < r_q && obs_col < c_q) {
                top_left = (r_q - obs_row - 1 < top_left) ? r_q - obs_row - 1 : top_left;
            }
            // Top-right diagonal
            else if (obs_row < r_q && obs_col > c_q) {
                top_right = (r_q - obs_row - 1 < top_right) ? r_q - obs_row - 1 : top_right;
            }
            // Bottom-left diagonal
            else if (obs_row > r_q && obs_col < c_q) {
                bottom_left = (obs_row - r_q - 1 < bottom_left) ? obs_row - r_q - 1 : bottom_left;
            }
            // Bottom-right diagonal
            else if (obs_row > r_q && obs_col > c_q) {
                bottom_right = (obs_row - r_q - 1 < bottom_right) ? obs_row - r_q - 1 : bottom_right;
            }
        }
    }

    // Sum up all valid moves
    return up + down + left + right + top_left + top_right + bottom_left + bottom_right;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** first_multiple_input = split_string(rtrim(readline()));

    int n = parse_int(*(first_multiple_input + 0));

    int k = parse_int(*(first_multiple_input + 1));

    char** second_multiple_input = split_string(rtrim(readline()));

    int r_q = parse_int(*(second_multiple_input + 0));

    int c_q = parse_int(*(second_multiple_input + 1));

    int** obstacles = malloc(k * sizeof(int*));

    for (int i = 0; i < k; i++) {
        *(obstacles + i) = malloc(2 * (sizeof(int)));

        char** obstacles_item_temp = split_string(rtrim(readline()));

        for (int j = 0; j < 2; j++) {
            int obstacles_item = parse_int(*(obstacles_item_temp + j));

            *(*(obstacles + i) + j) = obstacles_item;
        }
    }

    int result = queensAttack(n, k, r_q, c_q, k, 2, obstacles);

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
