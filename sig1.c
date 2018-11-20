#include <stdio.h>
#include <assert.h>
#include <signal.h>
#define TRUE 1

void myHandler(int iSig);

int main()
{
    void (*pfRet)(int) = signal(SIGINT, myHandler);
    assert(pfRet != SIG_ERR);

    printf("Entering an infinite loop\n");
    while (TRUE)
        printf(".");

        return 0;
}

void myHandler(int iSig)
{
    printf("In myHandler with argument %d\n", iSig);
}


