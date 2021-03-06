//Name :- Darshil Bhakhar
//Student Id :- 110025863

#include "smallsh.h"
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int runcommand(char **cline, int where)
{

	

	//for requirement 5 "|"

	int join(char *cmd1[], char *cmd2[], char *cmd3[])
	{
		int pid1, pid2;
		int fd[2];
		if ((pid1 = fork()) == -1)
		{
			perror("fork can not be done");
			exit(1);
		}

		else if (pid1 == 0)
		{
			if (pipe(fd) == -1)
			{
				perror("error in pipe");
				exit(4);
			}
			if (cmd3 != NULL)
			{
				if ((pid2 = fork()) == -1)
				{
					perror("fork can not be done");
					exit(1);
				}

				else if (pid2 == 0)
				{
					close(fd[0]);
					dup2(fd[1], 1); //for writing in pipe

					execvp(cmd1[0], cmd1);
					perror("error in execvp");
					exit(7);
				}
				else
				{
					if (pid2 > 0) //Parent process
					{
						close(fd[1]);
						dup2(fd[0], 0); //reading from pipe

						execvp(cmd2[0], cmd2);
						perror("error in execvp");
						exit(7);
					}
				}
			}

			{
				/* code */
			}
		}
		else
		{
			if (pid1 > 0)
			{ //Parent process
			}
		}
	if (0 == strcmp(cline[0], "join"))
	{
		char *one[4] = {"ls", "-lt", "more", NULL};

		char *two[2] = {"|", NULL};

		char *three[2] = {"more", NULL};

		int ret;

		ret = join(one, two, three);

		printf("join done.\n");
		return (0);
		exit(0);
	}


		pid_t pid;
		int status;
		switch (pid = fork())
		{
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
}