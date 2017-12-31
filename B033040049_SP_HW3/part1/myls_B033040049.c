#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/param.h>
#include <unistd.h>
#include <string.h>

int flagF=0,flagR=0;

void list_directory( char *dir_path );

int main( int argc, char* argv[] ) {
	
	char *dir;
	long pathmaxlen = pathconf(".", _PC_PATH_MAX);
	int i;
	
	if(argc > 1)
	{
		if(argv[1][0]=='-')
		{
			i=0;
			while(argv[1][i]!='\0')
			{
				if(argv[1][i]=='F')
					flagF=1;
				else if(argv[1][i]=='R')
					flagR=1;
				i++;
			}
		}
	}
	
	dir = getcwd((char*)NULL, pathmaxlen + 1);
	
	if(dir==NULL)
	{
		perror("getcwd");
		exit(1);
	}

	list_directory(dir);
	free(dir);

	return 0;
}

void list_directory( char *dir_path ) {

	struct stat buf;
	DIR *dirp;
	struct dirent *dent;

	if((dirp = opendir(dir_path)) == NULL)
	{
		perror("opendir");
		exit(1);
	}
	
	printf("\n%s\n",dir_path);
	char str2[255];

	while((dent = readdir(dirp)) != NULL)
	{
		if((strcmp(".",dent->d_name)!=0) && (strcmp("..",dent->d_name)))
		{
			printf("%s", dent->d_name);
			
			if(flagF==1)
			{
				strcpy(str2,dir_path);
				strcat(str2,"/");
				strcat(str2,dent->d_name);
				if(stat(str2,&buf) == -1)
				{
					perror("stat");
					exit(1);
				}
				if(S_ISREG(buf.st_mode))
				{
					if((buf.st_mode & 0x0040)==0x0040)
						printf("*");
				}
				else if(S_ISLNK(buf.st_mode))
				{
					printf("@");
				}
				else if(S_ISFIFO(buf.st_mode))
				{
					printf("|");
				}
				else if(S_ISSOCK(buf.st_mode))
				{
					printf("=");
				}
				else if(S_ISDIR(buf.st_mode))
				{
					printf("/");
				}
			}
			printf("\n");
		}
		
	}
	(void)closedir(dirp);

	if(flagR==1)
	{
		if((dirp = opendir(dir_path)) == NULL)
		{
			perror("opendir");
			exit(1);
		}
		while((dent = readdir(dirp)) != NULL)
		{
			if((strcmp(".",dent->d_name)!=0) && (strcmp("..",dent->d_name)))
			{
				strcpy(str2,dir_path);
				strcat(str2,"/");
				strcat(str2,dent->d_name);

				if(stat(str2,&buf) == -1)
				{
					perror("stat");
					exit(1);
				}
				if(S_ISDIR(buf.st_mode))
				{
					
					char str[255];
					strcpy(str,dir_path);
					strcat(str,"/");
					strcat(str,dent->d_name);
					list_directory(str);
				}
			}
		}
		(void)closedir(dirp);
	}
	
}
