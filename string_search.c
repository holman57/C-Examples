/**
 * Return the index of the first occurrence of needle in haystack,
 * or -1 if needle is not part of haystack.
 *
 * Example 1:
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 *
 * Example 2:
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 * */
int ft_strlen(const char *str) {
    int len;

    len = 0;
    while (str[len])
        len++;
    return (len);
}

int ft_strncmp(const char *str1, const char *str2, int n) {
    int i;

    i = -1;
    while (++i < n)
        if (str1[i] != str2[i])
            return (str1[i] - str2[i]);
    return (0);
}

int strStr(char *haystack, char *needle) {
    int n;
    int l;
    int i;

    if (needle == NULL || *needle == '\0')
        return (0);
    l = ft_strlen(haystack);
    n = ft_strlen(needle);
    i = -1;
    while (++i < l) {
        if (haystack[i] != needle[0])
            continue;
        if (i + n > l)
            break;
        if (ft_strncmp((haystack + i), needle, n) == 0)
            return (i);
    }
    return (-1);
}