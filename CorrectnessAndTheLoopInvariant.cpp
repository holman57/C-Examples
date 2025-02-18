#include <stdio.h>
#include <stdlib.h>

void insertionSort(int N, int arr[]) {
    int i, j, value;
    for (i = 1; i < N; i++) {
        value = arr[i];
        j = i - 1;
        // Fixing the `while` condition to allow comparison with arr[0]
        while (j >= 0 && value < arr[j]) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = value;
    }
}

int main(void) {
    int N;
    scanf("%d", &N);
    int arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    insertionSort(N, arr);

    // Print the sorted array
    for (int j = 0; j < N; j++) {
        printf("%d ", arr[j]);
    }

    return 0;
}