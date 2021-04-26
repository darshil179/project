//Name :- Darshil Bhakhar
//Student Id :- 110025863

#include "smallsh.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// command arg1 arg2 arg3
static char inpbuf[MAXBUF], tokbuf[2 * MAXBUF],
*ptr = inpbuf, *tok = tokbuf;

int inarg(char c);

int userin(char *p)
{
	char buffer[256];
	int size;

	char* pcwd = getcwd(buffer, 256);

	//if (0 == strcmp(cline[0], "cwd")) {
	//	return getcwd(buffer,sizeof(buffer));
	//}

	int c, count;
	ptr = inpbuf;
	tok = tokbuf;
	
//showing current directory for requirement 2

	printf("This is your current directory (location) %s$", pcwd);
	count = 0;
	printf("\n");
	

	//for exiting after 10 seconds if user doesn't give input requirement 4
	while (1)
	{
		printf("Enter input to start counting from beginning \n");
		printf("Waiting for input for 10 seconds \n");
		alarm(10);
		c = getchar();
		alarm(0);
		printf("Enter input to start counting from beginning \n");
		
		// if ((c == EOF)){
			
		// }
	}

	while (1)
	{
		if ((c = getchar()) == EOF)
			return(EOF);
		if (count < MAXBUF)
			inpbuf[count++] = c;
		if (c == '\n' && count < MAXBUF)
		{
			inpbuf[count] = '\0';
			return count;
		}
		
		if (c == '\n') 
		{
			printf("smallsh: input line too long\n");
			count = 0;
			printf("%s ", p);
		}

		
		
	}

	

//	printf("inpbuf=%s\n", inpbuf);
}

int gettok(char **outptr)
{
	int type;
	
	*outptr = tok;
	
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	
	*tok++ = *ptr;
	
	switch (*ptr++) {
	case '\n':
		type = EOL;
		break;
	case '&':
		type = AMPERSAND;
		break;
	case ';':
		type = SEMICOLON;
		break;
	default:
		type = ARG;
		
		while (inarg(*ptr))
			*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return type;
}

//****************************************************************************************
static char special[] = { ' ', '\t', '&', ';', '\n', '\0' };
int inarg(char c)
{
	char *wrk;
	for (wrk = special; *wrk; wrk++)
	{
		if (c == *wrk)
			return (0);
	}
	return (1);
}


