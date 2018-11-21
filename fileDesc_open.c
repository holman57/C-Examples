#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/file.h>
#include <unistd.h>
int main() 
{
	int fd1, fd2, fd3;

	fd1 = open("test.txt", O_RDWR | O_TRUNC);

	printf("fd1 = %i\n", fd1);

	write(fd1, "what's", 6);

	// Make a copy of fd1
	fd2 = dup(fd1);

	printf("fd2 = %i\n", fd2);

	write(fd2, " up", 3);

	// Close standard input
	close(0);

	// Make another copy of fd1
	fd3 = dup(fd1);

	printf("fd3 = %i\n", fd3);

	// Because 0 was the smallest file descriptor and now belongs to fd3
	write(0, " doc", 4);

	// Suplicate channel 3 to channel 2
	dup2(3,2);

	write(2, "?\n", 2);
}

