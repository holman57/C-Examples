#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *pString[] = {"pwd", "ls", "date", "who"};
    int i = 0;

    printf(" 0 = pwd \n 1 = ls \n 2 = date \n 3 = who \nEnter Number: ");
    scanf("%d", &i);

    execlp(pString[i], pString[i], (char *) 0 );
    printf("Warning! execlp failed...\n");

    return 0;
}
