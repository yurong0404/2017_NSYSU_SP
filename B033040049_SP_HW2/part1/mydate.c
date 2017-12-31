#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/types.h>

int main()
{
	static char delim[] = " :\n";
	char *line = malloc(sizeof(char)*40);
	char *token;
	char *date[7];
	char ampm[3];
	int count=0;

	time_t t;
	time(&t);	
	strcpy(line,ctime(&t));

	token = strtok(line,delim);
	while(token!=NULL)
	{
		char *str = malloc(10);
		strcpy(str,token);
		date[count] = str;
		count++;	
		token = strtok(NULL,delim);
	}

	if(atoi(date[3])>=12)
	{
		if(atoi(date[3])!=12)
			sprintf(date[3], "%d", atoi(date[3])-12);
		strcpy(ampm,"PM");
	}
	else
	{
		strcpy(ampm,"AM");
	}

	printf("%s %s(%s), %s  %s:%s %s\n",date[1],date[2],date[0],date[6],date[3],date[4],ampm);

	free(line);
	free(token);
	count = 0;
	for(count=0;count<=6;count++)
	{
		free(date[count]);
	}
	return 0;
}
