#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <string.h>
#include <wait.h>
#define TRUE 1
/*
Limited shell, accepts commands with no arguments.
-- demonstrates process groups, foreground terminal for signalling
-- disables SIGINT for parent process, not child
*/
int main()
{
    char inbuff[256];
    pid_t pid;

    // struct sigaction
    // {
    //      void       (*sa_handler)(int);
    //      void       (*sa_sigaction)(int, siginfo_t *, void *);
    //      sigset_t   sa_mask;
    //      int        sa_flags;
    //      void       (*sa_restorer)(void);
    //  };
    struct sigaction act;

    while (TRUE)
    {
        // int tcsetpgrp(int fd, pid_t pgrp);

        //       The function tcgetpgrp() returns the process group ID of the
        //       foreground process group on the terminal associated to fd, which must
        //       be the controlling terminal of the calling process.
        //
        //       The function tcsetpgrp() makes the process group with process group
        //       ID pgrp the foreground process group on the terminal associated to
        //       fd, which must be the controlling terminal of the calling process,
        //       and still be associated with its session.  Moreover, pgrp must be a
        //       (nonempty) process group belonging to the same session as the calling
        //       process.
        //
        //       If tcsetpgrp() is called by a member of a background process group in
        //       its session, and the calling process is not blocking or ignoring
        //       SIGTTOU, a SIGTTOU signal is sent to all members of this background
        //       process group.
        //
        // RETURN VALUE
        //
        //       When fd refers to the controlling terminal of the calling process,
        //       the function tcgetpgrp() will return the foreground process group ID
        //       of that terminal if there is one, and some value larger than 1 that
        //       is not presently a process group ID otherwise.  When fd does not
        //       refer to the controlling terminal of the calling process, -1 is
        //       returned, and errno is set appropriately.
        //
        //       When successful, tcsetpgrp() returns 0.  Otherwise, it returns -1,
        //       and errno is set appropriately.

        // getpgrp() : determines the process group ID of the calling process.
        //             If successful, getpgrp returns the process group ID of the calling process.
        tcsetpgrp(fileno(stdin), getpgrp());

        // SIG_DFL 	default signal handling
        // SIG_IGN 	signal is ignored
        act.sa_handler = SIG_IGN;

        // int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

        //       The sigaction() system call is used to change the action taken by a
        //       process on receipt of a specific signal.  (See signal(7) for an
        //       overview of signals.)
        //
        //       signum specifies the signal and can be any valid signal except
        //       SIGKILL and SIGSTOP.
        //
        //       If act is non-NULL, the new action for signal signum is installed
        //       from act.  If oldact is non-NULL, the previous action is saved in
        //       oldact.
        assert(sigaction(SIGINT, &act, NULL) == 0);

        printf("> ");
        scanf("%s", inbuff);

        pid = fork();

        switch (pid)
        {
            case -1:
                // error
                perror("fork");
                exit(EXIT_FAILURE);

            case 0:
                // Child

                // If the calling process is not already a session leader, setpgrp() sets the process
                // group ID of the calling process to the process ID of the calling process.
                // If setpgrp() creates a new session, then the new session has no controlling terminal.
                // The setpgrp() function has no effect when the calling process is a session leader.
                // Upon completion, setpgrp() shall return the process group ID.
                setpgrp();

                // The getpgid() function shall return the process group ID of the process whose process
                // ID is equal to pid. If pid is equal to 0, getpgid() shall return the process group ID
                // of the calling process. Upon successful completion, getpgid() shall return a process
                // group ID. Otherwise, it shall return (pid_t)-1 and set errno to indicate the error.
                tcsetpgrp(fileno(stdin), getpgid(pid));
                act.sa_handler = SIG_DFL;
                assert(sigaction(SIGINT, &act, NULL) == 0);
                execlp(inbuff, inbuff, (char *) 0);
                printf("execlp failed\n");
                exit(EXIT_FAILURE);

            default:
                // Parent
                
                setpgid(pid, pid);
                signal(SIGTTOU, SIG_IGN);
                tcsetpgrp(fileno(stdin), getpgid(pid));
                wait(NULL);
        }

        memset(inbuff, '\0', sizeof(inbuff));
    }

    return 0;
}


