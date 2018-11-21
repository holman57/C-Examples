#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Equivalent to "sort < file2 | uniq */

int main()
{
	int fd[2];

	// FILE *fopen(const char *pathname, const char *mode);
	
	  //       The fopen() function opens the file whose name is the string pointed
    //       to by pathname and associates a stream with it.
    //
    //       The argument mode points to a string beginning with one of the
    //       following sequences (possibly followed by additional characters, as
    //       described below):
    //
    //       r      Open text file for reading.  The stream is positioned at the
    //              beginning of the file.
    //
    //       r+     Open for reading and writing.  The stream is positioned at the
    //              beginning of the file.
    //
    //       w      Truncate file to zero length or create text file for writing.
    //              The stream is positioned at the beginning of the file.
    //
    //       w+     Open for reading and writing.  The file is created if it does
    //              not exist, otherwise it is truncated.  The stream is
    //              positioned at the beginning of the file.
    //
    //       a      Open for appending (writing at end of file).  The file is
    //              created if it does not exist.  The stream is positioned at the
    //              end of the file.
    //
    //       a+     Open for reading and appending (writing at end of file).  The
    //              file is created if it does not exist.  The initial file
    //              position for reading is at the beginning of the file, but
    //              output is always appended to the end of the file.
    //
    //       The mode string can also include the letter 'b' either as a last
    //       character or as a character between the characters in any of the two-
    //       character strings described above.  This is strictly for
    //       compatibility with C89 and has no effect; the 'b' is ignored on all
    //       POSIX conforming systems, including Linux.  (Other systems may treat
    //       text files and binary files differently, and adding the 'b' may be a
    //       good idea if you do I/O to a binary file and expect that your program
    //       may be ported to non-UNIX environments.)
    //
    //       See NOTES below for details of glibc extensions for mode.
    //
    //       Any created file will have the mode S_IRUSR | S_IWUSR | S_IRGRP |
    //       S_IWGRP | S_IROTH | S_IWOTH (0666), as modified by the process's
    //       umask value (see umask(2)).
    //
    //       Reads and writes may be intermixed on read/write streams in any
    //       order.  Note that ANSI C requires that a file positioning function
    //       intervene between output and input, unless an input operation
    //       encounters end-of-file.  (If this condition is not met, then a read
    //       is allowed to return the result of writes other than the most
    //       recent.)  Therefore it is good practice (and indeed sometimes
    //       necessary under Linux) to put an fseek(3) or fgetpos(3) operation
    //       between write and read operations on such a stream.  This operation
    //       may be an apparent no-op (as in fseek(..., 0L, SEEK_CUR) called for
    //       its synchronizing side effect).
    //
    //       Opening a file in append mode (a as the first character of mode)
    //       causes all subsequent write operations to this stream to occur at
    //       end-of-file, as if preceded the call:
    //
    //           fseek(stream, 0, SEEK_END);
    //
    //       The file descriptor associated with the stream is opened as if by a
    //       call to open(2) with the following flags:
    //
    //              ┌─────────────┬───────────────────────────────┐
    //              │fopen() mode │ open() flags                  │
    //              ├─────────────┼───────────────────────────────┤
    //              │     r       │ O_RDONLY                      │
    //              ├─────────────┼───────────────────────────────┤
    //              │     w       │ O_WRONLY | O_CREAT | O_TRUNC  │
    //              ├─────────────┼───────────────────────────────┤
    //              │     a       │ O_WRONLY | O_CREAT | O_APPEND │
    //              ├─────────────┼───────────────────────────────┤
    //              │     r+      │ O_RDWR                        │
    //              ├─────────────┼───────────────────────────────┤
    //              │     w+      │ O_RDWR | O_CREAT | O_TRUNC    │
    //              ├─────────────┼───────────────────────────────┤
    //              │     a+      │ O_RDWR | O_CREAT | O_APPEND   │
    //              └─────────────┴───────────────────────────────┘
	FILE *fp = fopen("file2", "r");
	dup2(fileno(fp), fileno(stdin));
	fclose(fp);
	pipe(fd);

	if (fork() == 0)
	{
        dup2(fd[1], fileno(stdout));
		close(fd[0]);
		close(fd[1]);
		execl("/usr/bin/sort", "sort", (char*) 0);
		exit(2);
	}
	else
	{
		dup2(fd[0], fileno(stdin));
		close(fd[0]);
		close(fd[1]);
		execl("/usr/bin/uniq", "uniq", (char*)0);
		exit(3);
	}

	return 0;
}

