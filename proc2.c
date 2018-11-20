#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int global_var = 6;

int main() 
{
	int local_var = 88;
	pid_t pid;

	printf("Before fork()\n");

	if((pid = fork()) == 0) 
	{
		// Child
		global_var++;
		local_var++;
	}
	else if (pid > 0) 
	{
		// Parent
		sleep(2);
	}
	else if (pid < 0) 
		perror("fork error");

	printf("pid = %d, global_var = %d, local_var = %d\n", getpid(), global_var, local_var);

	return 0;
}


