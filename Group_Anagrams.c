/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase,
typically using all the original letters exactly once.

Example 1:

Input: strs = ["eat","tea","tan","ate","nat","bat"]
Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:

Input: strs = [""]
Output: [[""]]
Example 3:

Input: strs = ["a"]
Output: [["a"]]
 * */
#define KEYLEN 128

typedef struct {
    char key[KEYLEN];
    int listSize;
    char **list;
    UT_hash_handle hh;
} Map;

int cmpFunc(const void *a, const void *b) { return *(char *) a - *(char *) b; }

char ***groupAnagrams(char **strs, int strsSize, int **columnSizes, int *returnSize) {
    Map *map = NULL, *elem = NULL, *tmp;
    char strBuf[KEYLEN], ***result;
    int mapIndx = 0;
    if (strsSize <= 0) return NULL;
    for (int i = 0; i < strsSize; i++) {
        strncpy(strBuf, strs[i], KEYLEN);
        qsort(strBuf, strlen(strs[i]), sizeof(char), cmpFunc);
        HASH_FIND_STR(map, strBuf, elem);
        if (!elem) {
            elem = malloc(sizeof(Map));
            strncpy(elem->key, strBuf, KEYLEN);
            elem->listSize = 1;
            elem->list = malloc(sizeof(char **));
            elem->list[0] = strs[i];
            HASH_ADD_STR(map, key, elem);
        } else {
            elem->listSize++;
            elem->list = realloc(elem->list, elem->listSize * sizeof(char **));
            elem->list[elem->listSize - 1] = strs[i];
        }
    }
    *returnSize = HASH_COUNT(map);
    result = malloc(*returnSize * sizeof(char **));
    *columnSizes = malloc(*returnSize * sizeof(int));
    HASH_ITER(hh, map, elem, tmp)
    {
        (*columnSizes)[mapIndx] = elem->listSize;
        result[mapIndx++] = elem->list;
    }
    return result;
}
