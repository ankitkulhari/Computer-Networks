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
void split(char* temp,char* str[]){
  str[0]=strtok(temp,"$");
  str[1]=strtok(NULL,"$");
}
int main(){
	char* grp[]={"g1","g2","g3","g4","g5"};
	struct pollfd pfd[5];
	for(int i=0;i<5;i++){
		mkfifo(grp[i],0666);
		pfd[i].fd=open(grp[i],O_RDONLY|O_NONBLOCK);
		pfd[i].events=POLLIN;
	}
  int fd[100];
	int which[100];
	memset(which,0,sizeof(which));
  int n=0;
  char temp[100];
  while(1){
    memset(temp,'\0',100);
		poll(pfd,5,10);
		for(int k=0;k<5;k++){
			if(pfd[k].revents & POLLIN){
				read(pfd[k].fd,temp,100);
				char *str[2];
		    split(temp,str);
		    if(atoi(str[0])>100){
		      printf("Process %s saying \" %s \" \nGrant Permission?(y/n)\n",str[0],str[1]);
		      char ch;
		      ch='y';
		      if(ch=='n'||ch=='N')  {continue;}
		      mkfifo(str[0],0666);
					fd[n]=open(str[0],O_WRONLY|O_NONBLOCK);
		      if(fd[n]==-1){
		        kill(atoi(str[0]),SIGKILL);
		        perror("Error in creating FIFO\n");
		        continue;
		      }
		      char tt[]={n+'0','\0'};
		      write(fd[n],tt,1);
					which[n]=(1<<k);
					printf("Granted permission clientno given %d\n",n);
		      n++;
		    }
		    else{
		      int j=atoi(str[0]);
					char ch2[]={k+'0','\0'};
					// printf("k== %d, which = %d\n",k,which[j]);
					if(!(which[j]&(1<<k))){
						printf("Client %s is asking to join %d (y/n)\n",str[0],k);
						char ch;//scanf(" %s",&ch);
						ch='y';
						if(ch=='n'||ch=='N')	continue;
						which[j]|=(1<<k);
					}
					printf("client %s: %s\n",str[0],str[1]);
					char temp2[100];memset(temp2,'\0',100);
					strcpy(temp2,str[0]);strcat(temp2,"$");
					strcat(temp2,ch2);strcat(temp2,"$");
					strcat(temp2,str[1]);strcat(temp2,"$");
		      for(int i=0;i<n;i++){
						if(j==i)	continue;
						if(which[i]&(1<<k))
							write(fd[i],temp2,strlen(temp2));
					}
		    }
			}
		}

  }
}
