#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define TRUE 1

int main() 
{
    char *pString[] = {"pwd", "ls", "date", "who"};
    int i = 0;

    while(TRUE)
    {
        printf(" 0 = pwd \n 1 = ls \n 2 = date \n 3 = who \nEnter Number: ");
        scanf("%d", &i);

        if (fork() == 0)
        {
            // Child
            execlp(pString[i], pString[i], (char *) 0 );
            printf("Warning! execlp failed...\n");
            exit(1);
        }
        else
        {
            // Parent
            wait((int *) 0);
            printf("child finished\n");
        }
    }
}
