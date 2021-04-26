//Name :- Darshil Bhakhar
//Student Id :- 110025863

#include "smallsh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int executesection(int* input, int* output, char **section) {
	pid_t pid;
	int status;
	switch (pid = fork()) {
		case -1:
			perror("smallsh");
			return (-1);
		case 0:
			if (input[0] != -1) {
				dup2(input[0], STDIN_FILENO);
				close(input[0]);
			}
			if (output[1] != -1) {

			}
			execvp(section[0], section);
			perror(*section);
			exit(1);
	}
	
}

int runcommand(char **cline, int where)
{
	// identify delimiters | of multiple commends
	// cline:
	// cd
	// ../
	// | 
	// pwd	
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

	
	// execute possible multiple commands
	const int maximumCmds = 7;
	int filedescriptors[maximumCmds][2];
	char** cmdsections[maximumCmds];
	cmdsections[0] = cline;
	int commandscount = 0;
	filedescriptors[0][0] = -1;
	filedescriptors[0][1] = -1;
	char *pitem;
	for (char** pstr = cline;pitem != NULL; pitem++) {
		if (*pstr == NULL || 0 == strcmp(*pstr, "|")) {
			pipe(filedescriptors[++commandscount]);
			cmdsections[commandscount] = pstr + 1;
		}
	}
	filedescriptors[commandscount][0] = -1;
	filedescriptors[commandscount][1] = -1;
	for (int i=0; i<commandscount; i++) {
		executesection(filedescriptors[i], filedescriptors[i+1], cmdsections[i]);
	}

	//code for parents
	// if (where == BACKGROUND)
	// {
	// 	printf("[process id %d]\n", pid);
	// 	return (0);
	// }
	
	// if (waitpid(pid, &status, 0) == -1)
	// 	return (-1);
	// else
	// 	return (status);

	// pid_t pid;
	// int status;
	// switch (pid = fork()) {
	// 	case -1:
	// 		perror("smallsh");
	// 		return (-1);
	// 	case 0:
	// 		execvp(cline[0], cline);
	// 		perror(*cline);
	// 		exit(1);
	// }
	// //code for parents
	// if (where == BACKGROUND)
	// {
	// 	printf("[process id %d]\n", pid);
	// 	return (0);
	// }
	
	// if (waitpid(pid, &status, 0) == -1)
	// 	return (-1);
	// else
	// 	return (status);
}
