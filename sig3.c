#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#define TRUE 1

void sig_user(int signal_number);

int main()
{
    int i = 0;

    // The SIGUSR1 and SIGUSR2 signals are set aside for you
    // to use any way you want. They're useful for simple
    // interprocess communication, if you write a signal handler
    // for them in the program that receives the signal. There
    // is an example showing the use of SIGUSR1 and SIGUSR2
    // in Signaling Another Process.
    if (signal(SIGUSR1, sig_user) == SIG_ERR)
        printf("Cannot catch SIGUSR1\n");

    if (signal(SIGUSR2, sig_user) == SIG_ERR)
        printf("Cannot catch SIGUSR2\n");

    while (TRUE)
    {
        printf( "%2d\n", i );

        // pause until signal handler has processed signal
        pause();

        i++;
    }

    return 0;
}

void sig_user(int signal_number)
{
    if (signal_number == SIGUSR1)
    {
        printf("Received SIGUSR1\n");
    }
    else if (signal_number == SIGUSR2)
    {
        printf("Received SIGUSR2\n");
    }
    else
        printf("Error: received signal %d\n", signal_number);
}


