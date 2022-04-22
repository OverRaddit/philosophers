#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int pid;
	int status;
	int ret;

	printf("BEFORE FORK\n");
	pid = fork();
	if (pid < 0)
		printf("FORK ERROR\n");
	else if (pid == 0)
	{	/* child process */
		printf("I'm child process\n");
		exit(0);
	}
	else
	{	/* parent process */
		ret = wait(&status);
		printf("I'm waiting until child exit!\n");
	}

	printf("AFTER FORK: %d\n", ret);
}