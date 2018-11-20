#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#define TRUE 1

void INThandler(int);

void main(void)
{
    // A process can replace the default signal handler
    // for almost all signals (but not SIGKILL) by its
    // user’s own handler function.

    // The SIGINT (“program interrupt”) signal is sent
    // when the user types the INTR character (normally C-c)
    signal(SIGINT, INThandler);
    
    while (TRUE)
    {
        pause();
    }

}

void  INThandler(int sig)
{
    char c;

    // SIG_IGN: Ignores the signal sig. Passing SIG_IGN as 
    // handler ignores a given signal ignores it (except the 
    // signals SIGKILL and SIGSTOP which can't caught or ignored).
    signal(sig, SIG_IGN);
    printf("OUCH, did you hit Ctrl-C?\n Do you really want to quit? [y/n] ");
    
    c = (char) getchar();
    
    if (c == 'y' || c == 'Y')
        exit (0);
    else
        signal(SIGINT, INThandler);
}

