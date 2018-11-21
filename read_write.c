#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define READ 0
#define WRITE 1

char *phrase = "Mario goes in the pipe";

int main()
{
    int fd[2], bytesRead;
    char message[100];

    pipe(fd);

    if (fork() == 0)
    {
        // Child
        close(fd[READ]);

        // ssize_t write(int fd, const void *buf, size_t count);

        // write() writes up to count bytes from the buffer pointed buf to the file referred to
        // by the file descriptor fd. The number of bytes written may be less than count if, for
        // example, there is insufficient space on the underlying physical medium, or the
        // RLIMIT_FSIZE resource limit is encountered (see setrlimit()), or the call was interrupted
        // by a signal handler after having written less than count bytes. (See also pipe().)
        // For a seekable file (i.e., one to which lseek() may be applied, for example, a regular
        // file) writing takes place at the current file offset, and the file offset is incremented
        // by the number of bytes actually written. If the file was open()ed with O_APPEND, the file
        // offset is first set to the end of the file before writing. The adjustment of the file offset
        // and the write operation are performed as an atomic step. POSIX requires that a read()
        // which can be proved to occur after a write() has returned returns the new data. Note that
        // not all file systems are POSIX conforming.
        //
        //      Return Value
        //
        // On success, the number of bytes written is returned (zero indicates nothing was written). 
        // On error, -1 is returned, and errno is set appropriately. If count is zero and fd refers 
        // to a regular file, then write() may return a failure status if one of the errors below is 
        // detected. If no errors are detected, 0 will be returned without causing any other effect. 
        // If count is zero and fd refers to a file other than a regular file, the results are not specified.
        write(fd[WRITE], phrase, strlen(phrase) + 1);

        printf("Child just sent the message to the parent.\n");
        close(fd[WRITE]);
    }
    else
    {
        // Parent
        close(fd[WRITE]);

        // ssize_t read(int fd, void *buf, size_t count);

        // read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.
        // On files that support seeking, the read operation commences at the current file offset, and the file 
        // offset is incremented by the number of bytes read. If the current file offset is at or past the end 
        // of file, no bytes are read, and read() returns zero.
        // If count is zero, read() may detect the errors described below. In the absence of any errors, or if 
        // read() does not check for errors, a read() with a count of 0 returns zero and has no other effects.
        // If count is greater than SSIZE_MAX, the result is unspecified.
        //
        //      Return Value
        //
        // On success, the number of bytes read is returned (zero indicates end of file), and the file 
        // position is advanced by this number. It is not an error if this number is smaller than the number 
        // of bytes requested; this may happen for example because fewer bytes are actually available right 
        // now (maybe because we were close to end-of-file, or because we are reading from a pipe, or from a 
        // terminal), or because read() was interrupted by a signal. On error, -1 is returned, and errno is 
        // set appropriately. In this case it is left unspecified whether the file position (if any) changes. 
        bytesRead = (int) read(fd[READ], message, 100);
        printf("Parent just read %i bytes: %s\n", bytesRead, message);
        close(fd[READ]);
    }

    return 0;
}

