#include "smallsh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int runcommand(char **cline, int where)
{
	if (0 == strcmp(cline[0], 'cd')) {
		return chdir(cline[1]);
	}


	pid_t pid;
	int status;
	switch (pid = fork()) {
		case -1:
			perror("smallsh");
			return (-1);
		case 0:
			execvp(cline[0], cline);
			perror(*cline);
			exit(1);
	}
	//code for parents
	if (where == BACKGROUND)
	{
		printf("[process id %d]\n", pid);
		return (0);
	}
	
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else
		return (status);
}
