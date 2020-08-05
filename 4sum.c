/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
    Given an array nums of n integers and an integer target, are there elements a, b, c, and d in nums such that
    a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target.

    Note: The solution set must not contain duplicate quadruplets.

    Example: Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

    A solution set is:
    [
      [-1,  0, 0, 1],
      [-2, -1, 1, 2],
      [-2,  0, 0, 2]
    ]
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void sortnums(int *nums, int numsSize) {
    for (int i = 0; i < numsSize; i++)
        for (int j = i + 1; j < numsSize; j++)
            if (nums[j] < nums[i]) {
                int tem = nums[i];
                nums[i] = nums[j];
                nums[j] = tem;
            }
}

void
recur(int ***output, int *returnSize, int **returnColumnSizes, int *nums, int numsSize, int *sub, int layer, int iter,
      int target) {
    if (layer < 4)
        for (int i = iter + 1; i < numsSize; i++) {
            sub[layer] = nums[i];
            if ((i > 0 && (nums[i] != nums[i - 1])) || i == iter + 1)
                recur(output, returnSize, returnColumnSizes, nums, numsSize, sub, layer + 1, i, target);
        }
    else {
        int t = 0;
        for (int i = 0; i < 4; i++)
            t += sub[i];
        if (t == target) {
            (*returnSize) += 1;
            (*output) = (int **) realloc((*output), (*returnSize) * sizeof(int *));
            (*returnColumnSizes) = (int *) realloc((*returnColumnSizes), (*returnSize) * sizeof(int));
            (*output)[(*returnSize) - 1] = (int *) malloc(4 * sizeof(int));
            (*returnColumnSizes)[(*returnSize) - 1] = 4;
            for (int i = 0; i < 4; i++)
                (*output)[(*returnSize) - 1][i] = sub[i];
        }
    }
}

int **fourSum(int *nums, int numsSize, int target, int *returnSize, int **returnColumnSizes) {
    int layer = 0;
    int iter = -1;
    (*returnSize) = 0;
    sortnums(nums, numsSize);
    int **output = (int **) malloc((*returnSize) * sizeof(int *));
    (*returnColumnSizes) = (int *) malloc((*returnSize) * sizeof(int));
    int *sub = (int *) malloc(4 * sizeof(int));
    recur(&output, returnSize, returnColumnSizes, nums, numsSize, sub, layer, iter, target);
    return output;
}