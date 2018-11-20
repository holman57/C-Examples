#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

void printpos(char *msg, int fd);

int main()
{
    int fd;
    pid_t pid;
    char buff[10];

    // int open(const char *pathname, int flags);
    // The open() system call opens the file specified by pathname.  If the
    // specified file does not exist, it may optionally (if O_CREAT is
    // specified in flags) be created by open().
    if ((fd = open("file1", O_RDONLY)) < 0)
        perror("open");

    // move R-W ptr
    // ssize_t read(int fd, void *buf, size_t count);
    // read() attempts to read up to count bytes from file descriptor fd
    // into the buffer starting at buf.
    read(fd, buff, 10);
    printpos("Before fork", fd );

    if ((pid = fork()) == 0)
    {
        // Child
        printpos("Child before read", fd);
        read(fd, buff, 10);
        printpos("Child after read", fd);
    }
    else if (pid > 0)
    {
        // Parent
        wait((int *) 0);
        printpos("Parent after wait", fd);
    }
    else if (pid < 0)
    {
        perror("fork");
    }
}

void printpos(char *msg, int fd)
{
    // Print position in file
    long int pos;

    // off_t lseek(int fd, off_t offset, int whence);
    // lseek() repositions the file offset of the open file description
    //       associated with the file descriptor fd to the argument offset
    //       according to the directive whence as follows:
    //
    //       SEEK_SET
    //              The file offset is set to offset bytes.
    //
    //       SEEK_CUR
    //              The file offset is set to its current location plus offset
    //              bytes.
    //
    //       SEEK_END
    //              The file offset is set to the size of the file plus offset
    //              bytes.
    if ((pos = lseek(fd, 0L, SEEK_CUR)) < 0L)
    {
        perror("lseek");
    }

    printf("%s: %ld\n", msg, pos);
}

