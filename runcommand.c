#include "smallsh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int runcommand(char **cline, int where)
{
	if (0 == strcmp(cline[0], "cd")) {
		int res = chdir(cline[1]);
		switch (res)
		{
		case ENOTDIR: perror("A component of path Not a directory"):
			/* code */
			break;

		case ENOENT: perror("No such file or directory"):
			/* code */
			break;	
		
		default:
		return res;
			break;
		}
	}

	// if (0 == strcmp(cline[0], "calculator")) {
	// 	char *path = "./dbq4.c"
	// 	execv(path, )
	// }

	if (0 == strcmp(cline[0], "exit")) {
		exit(0);
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
