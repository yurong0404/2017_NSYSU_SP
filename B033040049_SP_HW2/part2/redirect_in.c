/*
 * redirect_in.c  :  check for <
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "shell.h"
#define STD_OUTPUT 1
#define STD_INPUT  0

/*
 * Look for "<" in myArgv, then redirect input to the file.
 * Returns 0 on success, sets errno and returns -1 on error.
 */
int redirect_in(char ** myArgv) {
  	int i = 0;
  	int fd;

	while(myArgv[i]!=NULL)
	{
		if(strcmp(myArgv[i],"<")==0)
			break;
		i++;
	}
  	/* search forward for <
  	 *
	 * Fill in code. */

  	if (myArgv[i]) {	/* found "<" in vector. */

		fd = open(myArgv[i+1],O_RDONLY);
		
		if(fd == -1)
		{
			perror("open");
			return -1;
		}
		close(0);
		dup2(fd,0);
		close(fd);
		free(myArgv[i]);
		free(myArgv[i+1]);
		myArgv[i] = NULL;
		myArgv[i+1] = NULL;
    	/* 1) Open file.
     	 * 2) Redirect stdin to use file for input.
   		 * 3) Cleanup / close unneeded file descriptors.
   		 * 4) Remove the "<" and the filename from myArgv.
		 *
   		 * Fill in code. */
  	}
  	return 0;
}
