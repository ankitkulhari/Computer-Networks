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
#include<sys/select.h>
#include <sys/time.h>
void itoa(int i,char* s){
		int n=0;
		while(i){	char ch=i%10+'0';	s[n]=ch;i/=10;n++;}
		s[n]='\0';
		n--;i=0;
		while(i<n){	char t=s[i];s[i]=s[n];s[n]=t;	n--;i++;}
}
int main(){
	char wellKnowFifo[]="wellKnowFifo";
	int ret=mkfifo(wellKnowFifo,0666);
	int wellKnowFD=open(wellKnowFifo,O_WRONLY|O_NONBLOCK);
	pid_t pid=getpid();
	char pidc[100];
	itoa(pid,pidc);
	printf("Client NEW\n");
	int fd=mkfifo(pidc,0666);
	fd=open(pidc,O_RDONLY|O_NONBLOCK);
	int clientno=-1;
	char temp[100];

	fd_set readfds;
	struct timeval timeout;
	timeout.tv_sec=2;timeout.tv_usec=0;

	FD_ZERO(&readfds);
	FD_SET(0,&readfds);
	FD_SET(fd,&readfds);
 	int a=fd+1;

	// struct pollfd pfd[2];
	// pfd[0].fd=0;
	// pfd[1].fd=fd;
	// pfd[0].events=POLLIN;
	// pfd[1].events=POLLIN;

	char addDollor[]={'$','\0'};
	while(1){
			int hh=select(a,&readfds,NULL,NULL,&timeout);
			if(hh){

				if(FD_ISSET(0,&readfds)){
					char temp2[100];
					scanf("%[^\n]%*c",temp);
					if(clientno==-1)
						strcpy(temp2,pidc);
					else{
						memset(temp2,'\0',100);
						temp2[0]=clientno+'0';temp2[1]='\0';
					}
					strcat(temp2,addDollor);
					strcat(temp2,temp);strcat(temp2,addDollor);
					write(wellKnowFD,temp2,strlen(temp2));
				}
				if(FD_ISSET(fd,&readfds)){
					memset(temp,'\0',100);
					read(fd,temp,100);
					if(clientno==-1){
							clientno=temp[0]-'0';
							printf("Client no Received %d\n",clientno);
					}
					else
					{
						printf("%s\n",temp);
						char* token[2];
						token[0]=strtok(temp,"$");
						token[1]=strtok(NULL,"$");
						printf("%s : %s\n",token[0],token[1]);
					}
				}
			}
			FD_SET(0,&readfds);
			FD_SET(fd,&readfds);
	}
}