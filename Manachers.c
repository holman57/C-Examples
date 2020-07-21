/* Reference: 
 * https://en.wikipedia.org/wiki/Longest_palindromic_substring#Manacher.27s_algorithm
 * http://www.cnblogs.com/bitzhuwei/p/Longest-Palindromic-Substring-Part-II.html
 */

char* longestPalindrome(char* s) {
    int len = strlen(s);
    
    int length = (len << 1) + 1;
    char *str = (char *)malloc(sizeof(char) * length);
    int *p = (int *)malloc(sizeof(int) * length);
    for (int i = 0; i < length; ++i) {
        str[i] = i % 2 ? s[i / 2] : '\0';
        //p[i] = 0; // assigned when distance < 0
    }
    
    int mid = 0, right = 0;
    for (int i = 0; i < length; ++i) {
        int distance = right - i;
        int i_mirror = mid - (i - mid);
        
        if (distance > 0 && p[i_mirror] < distance) // when i is in the right mirror of a big palindrome, use the value of left mirror
            p[i] = p[i_mirror];
        else {
            p[i] = distance < 0 ? 0 : distance;
            while (i - p[i] - 1 >= 0 && i + p[i] + 1 < length
                && str[i - p[i] - 1] == str[i + p[i] + 1])
                ++p[i];
            mid = i;
            right = i + p[i];
        }
    }
    
    int pos = 0, maxlen = 0;
    for (int i = 0; i < length; ++i) {
        if (p[i] > maxlen) {
            pos = i;
            maxlen = p[i];
        }
    }
    
    free(str);
    free(p);
    
    char *res = s + (pos - maxlen) / 2;
    *(res + maxlen) = '\0';
    return res;
}