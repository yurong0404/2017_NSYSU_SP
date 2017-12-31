#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<string.h>

#define MAXSIZE 1024

int main()
{
	char buf[MAXSIZE];
	int pd[2];
	char *command[3] = {"ls","-l",NULL};

	memset(buf,0,MAXSIZE);
	if(pipe(pd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	switch(fork())
	{
		case -1:
			perror("fork");
			exit(1);
			break;
		case 0:
			close(pd[0]);
			dup2(pd[1],1);
			execvp(command[0],command);
			close(pd[1]);
			exit(0);
			break;
		default:
			wait(NULL);
			close(pd[1]);
			read(pd[0],buf,MAXSIZE);
			close(pd[0]);
			write(1,buf,MAXSIZE);
			break;
	}
	return 0;
}
