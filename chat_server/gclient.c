
to me

1st 2 chat server
next 4 data center
2 group chat
hamming code
chat server via msg queue - 2 program
than p1->p2->p3->p1
2 using select in chat server
2 using select in group chat
15 Attachments

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
void itoa(int i,char* s){int n=0;while(i){char ch=i%10+'0';	s[n]=ch;i/=10;n++;}
		s[n]='\0';n--;i=0;
		while(i<n){char t=s[i];s[i]=s[n];s[n]=t;n--;i++;}
}
int main(){
	char* grp[]={"g1","g2","g3","g4","g5"};
	int gfd[5];
	for(int i=0;i<5;i++)
	{
		mkfifo(grp[i],0666);
		gfd[i]=open(grp[i],O_WRONLY|O_NONBLOCK);
	}
	pid_t pid=getpid();
	char pidc[100];
	itoa(pid,pidc);
	printf("Client NEW\n");
	int fd=mkfifo(pidc,0666);
	fd=open(pidc,O_RDONLY|O_NONBLOCK);
	int clientno=-1;
	char temp[100];
	struct pollfd pfd[2];
	pfd[0].fd=0;
	pfd[1].fd=fd;
	pfd[0].events=POLLIN;
	pfd[1].events=POLLIN;
	char addDollor[]={'$','\0'};
	int which=0;
	while(1){
			poll(pfd,2,10);
			if(pfd[0].revents & POLLIN){
				char temp2[100];
				scanf("%[^\n]%*c",temp);	//input should be in grpno$data
				strcat(temp,addDollor);
				char* s=strtok(temp,"$");
				which=s[0]-'0';
				s=strtok(NULL,"$");
				//printf("which := %d data:= %s\n",which,s);

				strcpy(temp,s);
				if(clientno==-1)
					strcpy(temp2,pidc);
				else{
					memset(temp2,'\0',100);
					temp2[0]=clientno+'0';temp2[1]='\0';
				}
				strcat(temp2,addDollor);
				strcat(temp2,temp);strcat(temp2,addDollor);
				write(gfd[which],temp2,strlen(temp2));
			}
			if(pfd[1].revents & POLLIN){
				memset(temp,'\0',100);
				read(fd,temp,100);
				if(clientno==-1){
						clientno=temp[0]-'0';
						printf("Client no Received %d\n",clientno);
				}
				else
				{
					printf("%s\n",temp);
					char* token[3];
					token[0]=strtok(temp,"$");
					token[1]=strtok(NULL,"$");
					token[2]=strtok(NULL,"$");
					printf("%s -> client %s : %s\n",token[1],token[0],token[2]);
				}
			}
	}
}