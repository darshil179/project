//Name :- Darshil Bhakhar
//Student Id :- 110025863

#include "smallsh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int runcommand(char **cline, int where)
{
	//Change directory for requirement 1
	if (0 == strcmp(cline[0], "cd")) {
		int res = chdir(cline[1]);
					// error handling
		switch (res)
		{
		case ENOTDIR: perror("A component of path Not a directory");
			/* code */
			break;

		case ENOENT: perror("No such file or directory");
			/* code */
			break;

		case EACCES: perror("Permission denied");
			break;
		case EIO:	 perror("An input output error occured");
			break;
		case ENAMETOOLONG: perror("Path is to long");
			break;		
		
		default:
		return res;
			break;
		}
	}

	//for requirement 7 "Calculator"
	if (0 == strcmp(cline[0], "calculator")) {
		//char *path = "./dbq4.c"
		execl("./dbq4","",(char *)NULL);
	}

	//Requirement 3 user types exit program will terminate
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
