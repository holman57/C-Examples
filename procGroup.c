#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t child_pid, pid, procGroup_id, childProcGroup_id;

    if ((child_pid = fork()) == 0)
    {
        //      Child

        // If the calling process isn't already a session leader, setpgrp()
        // makes it one by setting its process group ID and session ID to the
        // value of its process ID, and releases its controlling terminal.
        setpgrp();

        // print the pid, and procGroup_id of child from child
        pid = getpid();
        procGroup_id = getpgrp();
        printf("Child:\t\t\tpid:%d  procGroup_id: *%d*\n", pid, procGroup_id);
    }
    else if (child_pid > 0)
    {
        //      Parent

        // setpgid() is used either to join an existing process group or to create
        // a new process group. The process specified by pid, or the calling process
        // if pid is 0, is joined to the process group whose ID is pgid. If pgid is
        // not an existing process group ID, then pgid must equal pid or be 0; in
        // which case a new process group with ID pid is created.
        setpgid(child_pid, child_pid);

        // print the pid, and procGroup_id of parent
        pid = getpid();
        procGroup_id = getpgrp();
        printf("Parent:\t\t\tpid:%d  procGroup_id:  %d \n", pid, procGroup_id);

        // print the pid, and procGroup_id of child from parent
        childProcGroup_id = getpgid(child_pid);
        printf("Parent: Child's\t\tpid:%d  procGroup_id: *%d*\n", child_pid, childProcGroup_id);
    }
    else if (child_pid < 0)
    {
        // Error
        perror("fork");
        exit(1);
    }

    return 0;
}

