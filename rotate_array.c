
void rotate(int **a, int n, int *matrixColSize) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            a[i][j] ^= a[j][i];
            a[j][i] ^= a[i][j];
            a[i][j] ^= a[j][i];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0, k = n - 1; j < k; j++, k--) {
            a[i][j] ^= a[i][k];
            a[i][k] ^= a[i][j];
            a[i][j] ^= a[i][k];
        }
    }
}