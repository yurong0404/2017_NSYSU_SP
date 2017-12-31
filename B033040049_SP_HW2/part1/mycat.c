#include<stdio.h>
#include<sys/types.h>
#include<sys/param.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define MAXSIZE 256

int main(int argc, char* argv[])
{
	int fd,n;
	char array[MAXSIZE];
	char *dir;
	long pathmaxlen = pathconf(".",_PC_PATH_MAX);

	dir = getcwd((char*)NULL,pathmaxlen+1);
	if(dir==NULL)
	{
		perror("getcwd");
		exit(1);
	}
	
	strcat(dir,"/");
	strcat(dir,argv[1]);
	fd = open(dir,O_RDONLY);

	if(fd==-1)
	{
		perror("open");
		exit(1);
	}
	
	while((n = read(fd, array, MAXSIZE)) > 0)
	{
		if(write(STDOUT_FILENO,array,n) !=n)
		{
			perror("write");
		}
	}
	
	if(n==-1)
	{
		perror("read");
	}

	free(dir);
	return 0;
}
