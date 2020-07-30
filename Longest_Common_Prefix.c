int lcp2(char *s1, int len1, char *s2, int len2)
{
    int i = 0;
    for (; i < len1 && i < len2; i++)
        if (s1[i] != s2[i])
            break;
    //printf("lcp of %.*s and %.*s is of size %d\n", len1, s1, len2, s2, i);
    return i;
}

int lcp_rec(char **strs, int size)
{
    if (size == 1)
        return strlen(strs[0]);
    int pref1 = lcp_rec(strs, size / 2);
    int pref2 = lcp_rec(strs + size / 2, size - (size / 2));
    int pref = lcp2(strs[0], pref1, strs[size / 2], pref2);
    return pref;
}

char *longestCommonPrefix(char **strs, int strsSize)
{
    if (strsSize == 0)
        return "";
    int len = lcp_rec(strs, strsSize);
    char *result = malloc(sizeof(char) * len + 1);
    strncpy(result, strs[0], len);
    result[len] = '\0';
    return result;
}