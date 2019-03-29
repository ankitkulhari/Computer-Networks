#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PATH "SFIFO"

char* itoa(int val)
{
	char *b,*h;
	b = malloc(sizeof(char)*40);
	h = malloc(sizeof(char)*40);
	while(val)
	{
		int r = val%10;
		char tmp[2];
		tmp[0] = r+48;
		tmp[1] = '\0';
		strcat(b,tmp);
		val/=10;
	}
	for(int i=strlen(b)-1;i>=0;i--)
	{
		char tmp[2];
		tmp[0] = b[i];
		tmp[1] = '\0';
		strcat(h,tmp);
	}
	return h;
}

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("Not enough arguments!\n");
		exit(1);
	}
	int fd,retval;
	int p = getpid();
	char *g = itoa(p);
	char *y;
	y = malloc(sizeof(char)*40);
	strcpy(y,g);
	strcat(g,"|");
	int u = atoi(argv[1]);
	if(u%2==1)
		strcat(g,"1");
	else
		strcat(g,"3");

	fd = open(PATH,O_WRONLY);
	write(fd,g,sizeof(g));

	int pfd = open(y,O_WRONLY);
	return 0;
}