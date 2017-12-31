/*
 * is_background.c :  check for & at end
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

int is_background(char ** myArgv) {

  	if (*myArgv == NULL)
    	return 0;

  	int i =0;
	while(myArgv[i]!=NULL)
	{
		i++;
	}
	if(strcmp(myArgv[i-1],"&")==0)
	{
		free(myArgv[i-1]);
		myArgv[i-1] = NULL;
		return 1;
	}
	else
		return 0;

}
