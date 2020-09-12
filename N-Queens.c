/**
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two
queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.'
both indicate a queen and an empty space respectively.

Example:

Input: 4
Output: [
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
Explanation: There exist two distinct solutions to the 4-queens puzzle as shown above.

    Return an array of arrays of size *returnSize.
    Note: The returned array must be malloced, assume caller calls free().
*/
void save(int n, int *cols, char ****res, int *size, int *returnSize) {
    if (*returnSize == *size) {
        *size += 1000;
        *res = realloc(*res, *size * sizeof(char **));
    }
    (*res)[(*returnSize)] = malloc(n * sizeof(char *));
    int i;
    for (i = 0; i < n; i++) {
        (*res)[(*returnSize)][i] = malloc(n + 1);
    }
    for (i = 0; i < n; i++) {
        int rowid = cols[i] - 1;
        int k;
        memset((*res)[(*returnSize)][rowid], '.', i);
        (*res)[(*returnSize)][rowid][i] = 'Q';
        memset((*res)[(*returnSize)][rowid] + i + 1, '.', n - 1 - i);
        (*res)[(*returnSize)][rowid][n] = '\0';
    }
    (*returnSize)++;
}

void search(int n, int r, int *cols, int *slash, int *bslash, char ****res, int *size, int *returnSize) {
    if (r == n) {
        save(n, cols, res, size, returnSize);
        return;
    }
    int c;
    for (c = 0; c < n; c++) {
        if (cols[c] || slash[n - 1 - c + r] || bslash[r + c]) continue;
        cols[c] = r + 1;
        slash[n - 1 - c + r] = 1;
        bslash[r + c] = 1;
        search(n, r + 1, cols, slash, bslash, res, size, returnSize);
        cols[c] = 0;
        slash[n - 1 - c + r] = 0;
        bslash[r + c] = 0;
    }
}

char ***solveNQueens(int n, int *returnSize) {
    int size = 1000;
    char ***res = malloc(size * sizeof(char **));
    *returnSize = 0;
    int *cols = calloc(n, sizeof(int));
    int *slash = calloc(2 * n - 1, sizeof(int));
    int *bslash = calloc(2 * n - 1, sizeof(int));
    int row = 0;
    search(n, row, cols, slash, bslash, &res, &size, returnSize);
    return res;
}
