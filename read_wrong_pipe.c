#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define READ 0
#define WRITE 1

char* phrase = "Another pipe example end closed";

void signal_catcher(int);

int main() 
{
	int fd[2], bytesWritten = 0, bytesRead;
	char message[100];

	signal(SIGPIPE, signal_catcher);

	pipe(fd);

	// Close used end
	close(fd[WRITE]);

	printf("About to read from pipe\n");

	bytesRead = read(fd[READ], message, 100);

	printf("%i bytes were read with write closed\n", bytesRead);

	// Close used end
	close(fd[READ]);

	// Recreate unnamed pipe
	pipe(fd);

	// Close unused end
	close(fd[READ]);

	printf("About to write to pipe\n");

	bytesWritten = write(fd[WRITE], phrase, strlen(phrase) + 1);

	printf("%i bytes were written with read end closed\n", bytesWritten);
	
	close(fd[WRITE]);
}

void signal_catcher(int theSig) 
{
	printf("A SIGPIPE (%i) has been caught\n", theSig);
}

