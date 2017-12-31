/*
 * parse.c : use whitespace to tokenise a line
 * Initialise a vector big enough
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"

/* Parse a commandline string into an argv array. */
char ** parse(char *line) {
static char delim[] = " \t\n"; /* SPACE or TAB or NL */
  	int count = 0;
  	char * token;
  	char **newArgv;

  	/* Nothing entered. */
  	if (line == NULL) 
	{
    	return NULL;
  	}
	
	newArgv = malloc(255*sizeof(char*));
	
	token = strtok(line,delim);
	while(token!=NULL)
	{
		char *str = malloc(255);
		strcpy(str,token);
		newArgv[count] = str;
		count++;	
		token = strtok(NULL,delim);
	}
	newArgv[count] = NULL;
	

  	return newArgv;
}


/*
 * Free memory associated with argv array passed in.
 * Argv array is assumed created with parse() above.
 */
void free_argv(char **oldArgv) {

	int i = 0;
	while(oldArgv[i]!=NULL)
	{
		free(oldArgv[i]);
		i++;
	}
	
	free(oldArgv);
}
