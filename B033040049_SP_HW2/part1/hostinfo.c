#include<stdio.h>
#include<stdlib.h>
#include<sys/utsname.h>
#include<unistd.h>

#define BUFSIZE 1024

int main()
{
	struct utsname uts;
	int hostid;

	if(uname(&uts)==-1)
	{
		perror("uname fail.");
		exit(1);
	}
	
	if((hostid = gethostid())==-1)
	{
		perror("gethostid");
		exit(1);
	}

	printf("hostname: %s\n",uts.nodename);
	printf("%s %s\n",uts.sysname,uts.release);
	printf("hostid: %d\n",hostid);
	return 0;
}
