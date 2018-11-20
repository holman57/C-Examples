#include <stdio.h>
#include <assert.h>
#include <signal.h>
#define TRUE 1

void myHandler(int iSig);

int main()
{
    // void (*signal(int sig, void (*func)(int)))(int)

    // typedef void (*sighandler_t)(int);
    // sighandler_t signal(int signum, sighandler_t handler);

    //       The behavior of signal() varies across UNIX versions, and has also
    //       varied historically across different versions of Linux.  Avoid its
    //       use: use sigaction(2) instead.  See Portability below.
    //
    //       signal() sets the disposition of the signal signum to handler, which
    //       is either SIG_IGN, SIG_DFL, or the address of a programmer-defined
    //       function (a "signal handler").
    //
    //       If the signal signum is delivered to the process, then one of the
    //       following happens:
    //
    //       *  If the disposition is set to SIG_IGN, then the signal is ignored.
    //
    //       *  If the disposition is set to SIG_DFL, then the default action
    //          associated with the signal (see signal(7)) occurs.
    //
    //       *  If the disposition is set to a function, then first either the
    //          disposition is reset to SIG_DFL, or the signal is blocked (see
    //          Portability below), and then handler is called with argument
    //          signum.  If invocation of the handler caused the signal to be
    //          blocked, then the signal is unblocked upon return from the
    //          handler.
    //
    //       The signals SIGKILL and SIGSTOP cannot be caught or ignored.
    //
    // RETURN VALUE
    //
    //       signal() returns the previous value of the signal handler, or SIG_ERR
    //       on error.  In the event of an error, errno is set to indicate the
    //       cause.
    void (*pfRet)(int) = signal(SIGINT, myHandler);
    assert(pfRet != SIG_ERR);

    printf("Entering an infinite loop\n");
    while (TRUE)
    {
        printf(".");
    }

    return 0;
}

void myHandler(int iSig)
{
    printf("In myHandler with argument %d\n", iSig);
}


