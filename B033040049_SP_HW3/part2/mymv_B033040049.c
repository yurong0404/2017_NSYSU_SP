#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main( int argc, char* argv[] ) {

	struct stat buf;
	int moveToDir=0;
	char str[256],str2[256];
	int newFileFd,oldFileFd;
	char *dir;
	long pathmaxlen = pathconf(".", _PC_PATH_MAX);
	int n;

	if(argc < 3)
	{
		printf("arguments!");
		exit(0);
	}

	if(access(argv[2],F_OK)!=-1)
	{
		if(stat(argv[2],&buf) == -1)
		{
			perror("stat");
			exit(1);
		}
		if(S_ISDIR(buf.st_mode))
		{
			moveToDir = 1;
		}
	}
	
	
	if(moveToDir == 1)
	{
		if(stat(argv[1],&buf) == -1)
		{
			perror("stat");
			exit(1);
		}
		dir = getcwd((char*)NULL, pathmaxlen + 1);
	
		if(dir==NULL)
		{
			perror("getcwd");
			exit(1);
		}
		strcpy(str,dir);
		strcat(str,"/");
		strcat(str,argv[2]);
		strcat(str,"/");
		strcat(str,argv[1]);

		if(access(str,F_OK)!=-1)
		{
			printf("mymv: overwrite '%s'?(Y/N)",argv[1]);
			fgets(str2,255,stdin);
			if( (strcmp(str2,"Y\n")!=0) && (strcmp(str2,"y\n")!=0) )
			{
				goto l1;
			}
			remove(str);
		}

		newFileFd = open(str,O_RDWR | O_CREAT);
		oldFileFd = open(argv[1],O_RDONLY);

		if(chmod(str,buf.st_mode) == -1)
		{
			perror("chmod");
			exit(1);
		}
		while ((n = read(oldFileFd,str,256)) > 0)
		{
			if(write(newFileFd, str, n) != n)
			{
				perror("write");
			}
		}

		close(newFileFd);
		close(oldFileFd);
		remove(argv[1]);
		l1:;
		free(dir);
	}

	else if(moveToDir == 0)
	{
		if(access(argv[2],F_OK)!=-1)
		{
			printf("mymv: overwrite '%s'?(Y/N)",argv[2]);
			fgets(str,255,stdin);
			if( (strcmp(str,"Y\n")==0) || (strcmp(str,"y\n")==0) )
			{
				rename(argv[1],argv[2]);
			}
		}
		else
		{
			rename(argv[1],argv[2]);
		}
	}
	return 0;
}
