/*
Given a collection of distinct integers, return all possible permutations.

Example:

Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
 * */
void swap(int *p, int *q) {
    int t = *p;
    *p = *q;
    *q = t;
}

void search(int *nums, int size, int ***arr, int *returnSize, int begin, int end) {
    if (begin == end) {
        (*returnSize)++;
        *arr = (int **) realloc(*arr, sizeof(int *) * (*returnSize));
        (*arr)[*returnSize - 1] = (int *) malloc(sizeof(int) * size);
        for (int i = 0; i < size; i++)
            (*arr)[*returnSize - 1][i] = nums[i];
        return;
    }
    for (int i = begin; i <= end; i++) {
        swap(nums + begin, nums + i); //try to use each element as the head;
        search(nums, size, arr, returnSize, begin + 1, end);
        swap(nums + begin, nums + i);
    }
}

int **permute(int *nums, int size, int *returnSize) {
    *returnSize = 0;
    int **arr = (int **) malloc(sizeof(int *));
    search(nums, size, &arr, returnSize, 0, size - 1);
    return arr;
}