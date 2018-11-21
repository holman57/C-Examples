#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int fd;
    
    // Open file for redirection
    
    // int open(const char *pathname, int flags);
    // int open(const char *pathname, int flags, mode_t mode);
    //
    //    The argument 'pathname' (as the name suggests) is the complete (or relative) path of the file 
    //    on system. Since there is also a cap on maximum length of a file name or maximum length of file 
    //    path in Linux. So, lets say if the maximum length of file name is 14 and if the file name specified 
    //    in the 'pathname' argument is greater then 14 characters then the filename could well be silently 
    //    truncated to 14 characters. This can cause problems in case the truncated file name matches the 
    //    name of an existing file. So to check whether truncations on file name and file path happen silently 
    //    or an error is returned, the macro _POSIX_NO_TRUNC can be used. If this macro is in effect then the 
    //    global error indicator errno is set to ENAMETOOLONG.
    //
    //    The argument 'flags' defines the way in which the file needs to be opened ie in read-only, 
    //    write-only or read-write mode. So corresponding to this there are three flags O_RDONLY, O_WRONLY, 
    //    or O_RDWR to choose from. So, one of these three flags is mandatory. Other than this, there are 
    //    some other flags that can be or'ed together and passed as part of this argument. These flags are : 
    //
    //    O_APPEND : The file is opened in append mode.
    //
    //    O_ASYNC : Enable signal-driven I/O ie generate a signal (SIGIO by default) when input or output 
    //              becomes possible on this file descriptor.
    //
    //    O_CLOEXEC : Enable the close-on-exec flag for the new file descriptor. This flag was introduced 
    //                since Linux 2.6.23
    //
    //    O_CREAT : If the file does not exist it will be created.
    //
    //    O_DIRECT : Try to minimize cache effects of the I/O to and from this file. This flag was 
    //               introduced since Linux 2.4.10
    //
    //    O_DIRECTORY : If pathname is not a directory, cause the open to fail.
    //
    //    O_EXCL : Ensure that this call creates the file: if this flag is specified in conjunction with 
    //             O_CREAT, and pathname already exists, then open() will fail. The behavior of O_EXCL 
    //             is undefined if O_CREAT is not specified.
    //
    //    O_LARGEFILE : (LFS) Allow files whose sizes cannot be represented in an off_t (but can be 
    //                  represented in an off64_t) to be opened. The _LARGE‐FILE64_SOURCE macro must 
    //                  be defined in order to obtain this definition.
    //
    //    O_NOATIME : Do not update the file last access time (st_atime in the inode) when the file is 
    //                read(2). This flag is intended for use by indexing or backup programs, where its 
    //                use can significantly reduce the amount of disk activity. This flag was introduced 
    //                since Linux 2.6.8
    //
    //    O_NOCTTY : If pathname refers to a terminal device — it will not become the process's controlling 
    //               terminal even if the process does not have one. O_NOFOLLOW : If pathname is a 
    //               symbolic link, then the open fails.
    //
    //    O_NONBLOCK : When possible, the file is opened in non-blocking mode. Neither the open() nor 
    //                 any subsequent operations on the file descriptor which is returned will cause 
    //                 the calling process to wait. This option is equivalent to O_NODELAY option.
    //
    //    O_SYNC : The file is opened for synchronous I/O. Any write on the resulting file descriptor 
    //             will block the calling process until the data has been physically written to the 
    //             underlying hardware.
    //
    //    O_TRUNC : If the file already exists and is a regular file and the open mode allows writing 
    //              (i.e., is O_RDWR or O_WRONLY) it will be truncated to length 0. If the file is a 
    //              FIFO or terminal device file, the O_TRUNC flag is ignored. Otherwise the effect 
    //              of O_TRUNC is unspecified.
    //
    //    As mentioned above, the O_NONBLOCK is same as O_NODELAY option flag. But there is something 
    //    worth mentioning regarding the O_NODELY option. If this option is used then a read operation 
    //    would return 0 in case there is no more data to read from a pipe, FIFO etc. But this return 
    //    value of 0 is in direct conflict with return value of 0 when end of file is encountered. 
    //    So it is preferable to use the O_NONBLOCK option. 
    fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);

    // Duplicate descriptor to standard output
    dup2(fd, 1);

    // Close original descriptor to save descriptor space
    close(fd);

    // Invoke program; will inherit stdout
    
    // When execvp() is executed, the program file given by the first argument will be loaded into 
    // the caller's address space and over-write the program there. Then, the second argument will 
    // be provided to the program and starts the execution. As a result, once the specified program 
    // file starts its execution, the original program in the caller's address space is gone and is 
    // replaced by the new program. 
    execvp(argv[2], &argv[2]);

    // Should never execute
    perror("main");
}


