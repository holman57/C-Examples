#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    pid_t pid;
    int i = 0, max_number = 150, minimum_number = 5;

    srand((unsigned int) time(0));
    int random = (rand() % (max_number - minimum_number + 1)) + minimum_number;

    pid = fork();

    printf("\t( pid = %d )\n", pid);

    if (pid > 0)
    {
        // Parent
        for (i = 0; i < random; i++)
            printf("PARENT %d\n", i);
    }
    else
    {
        // Child
        for (i = 0; i < random; i++)
            printf("CHILD %d\n", i);
    }

    return 0;
}

