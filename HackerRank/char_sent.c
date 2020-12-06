#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
/**
 * https://www.hackerrank.com/challenges/playing-with-characters/problem
 *
 * You have to print the character, 'ch', in the first line.
 * Then print 's' in next line. In the last line print the sentence, 'sen'.
 *
 * Sample Input
 *      C
 *      Language
 *      Welcome To C!!
 *
 * Sample Output
 *      C
 *      Language
 *      Welcome To C!!
 * */
int main()
{
    int MAX_LEN = 256;
    char ch;
    char **s[MAX_LEN];
    scanf("%c", &ch);
    scanf("%[^\n]%*c", s);

    printf("%c", ch);
    return 0;
}