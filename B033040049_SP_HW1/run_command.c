/*
 * run_command.c :    do the fork, exec stuff, call other functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

void run_command(char **myArgv) {
	pid_t pid;
	int stat;
	int i;

	pid = fork();

    switch (pid) {

        case -1 :
            perror("fork");
            exit(errno);

        default :
			//printf("parent:%d\n%s\n",myArgv,myArgv[0]);
			if(is_background(myArgv)==0)
			{
				wait(&stat);
				printf("exit status : %d\n",stat);
			}            
			return;

        case 0 :
			if(is_background(myArgv)==1)
			{
				i=0;
				while(strcmp(myArgv[i],"&")!=0)
				{
					i++;
				}
				free(myArgv[i]);
				myArgv[i] = NULL;
			}
			if(execvp(myArgv[0],myArgv)<0)
				perror("Err on execvp");
			exit(errno);
    }
}
