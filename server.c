#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define PATH "SFIFO"
// #define PF "cfifo"

int main()
{
	printf("%s\n", __DATE__);
	/*
	int fd,retval;
	retval = mkfifo(PATH,0666);
	char* buf;
	buf = malloc(sizeof(char)*40);
	fd = open(PATH,O_RDONLY);
	for(int i=0;i<2;i++)
	{
		read(fd,buf,sizeof(buf));
		char *h;
		int u;
		h  = malloc(sizeof(char)*40);
		// strcpy(h,PF);
		for(int i=0;i<strlen(buf);i++)
		{
			if(buf[i] == '|')
			{
				u = buf[i+1]-48;
				break;
			}
			char tmp[2];
			tmp[0] = buf[i];
			tmp[1] = '\0';
			strcat(h,tmp);
		}
		printf("received from client %s\n", h);
		if(mkfifo(h,0666)==0)
		{
			int ffd;
			if(u==1)
			{
				FILE *fp = popen("./d1","r");
				ffd = fileno(fp);
			}	
			else	
			{
				FILE *fp = popen("./d3","r");
				ffd = fileno(fp);
			}
		}
		else
		{
			perror("mkfifo");
			exit(1);
		}
		int ufd = open(h,O_RDONLY);
		// dup2(ffd,ufd);
	}*/
	return 0;
}