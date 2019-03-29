#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<signal.h>
#include <unistd.h>
#include <fcntl.h>
#include<poll.h>
void itoa(int i,char* s)
{
	int n=0;
	while(i)
	{	
		char ch=i%10+'0';
		s[n]=ch;
		i/=10;
		n++;
	}
	s[n]='\0';
	n--;
	i=0;
	while(i<n)
	{	
		char t=s[i];
		s[i]=s[n];
		s[n]=t;	
		n--;
		i++;
	}
}
int main()
{
	char mainfifo[]="wellKnowFifo";
	int ret=mkfifo(mainfifo,0666);
	int wellKnowFD=open(mainfifo,O_WRONLY|O_NONBLOCK);
	pid_t pid=getpid();
	char pidc[100];
	itoa(pid,pidc);


	printf("New client\n");
	int fd=mkfifo(pidc,0666);
	fd=open(pidc,O_RDONLY|O_NONBLOCK);
	int clientno=-1;
	char temp[100];
	struct pollfd pfd[2];

	pfd[0].fd=0;
	pfd[1].fd=fd;
	pfd[0].events=POLLIN;
	pfd[1].events=POLLIN;

	char delim[2];
	delim[0]='$';
	delim[1]='\0';
	while(1)
	{
			poll(pfd,2,10);
			if(pfd[0].revents & POLLIN)
			{
				char temp2[100];
				scanf("%[^\n]%*c",temp);
				if(clientno==-1)
					strcpy(temp2,pidc);
				else
				{
					memset(temp2,'\0',100);
					temp2[0]=clientno+'0';
					temp2[1]='\0';
				}
				strcat(temp2,delim);
				strcat(temp2,temp);
				strcat(temp2,delim);
				write(wellKnowFD,temp2,strlen(temp2));
			}
			if(pfd[1].revents & POLLIN)
			{
				memset(temp,'\0',100);
				read(fd,temp,100);
				if(clientno==-1)
				{
					clientno=temp[0]-'0';
					clientno+=48;
					printf("number assigned by server  %d\n",clientno);
				}
				else
				{
					char* token[2];
					token[0]=strtok(temp,"$");
					token[1]=strtok(NULL,"$");
					printf("%s : %s\n",token[0],token[1]);
				}
			}
	}
}