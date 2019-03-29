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
void itoa(int i,char* s){
		int n=0;
		while(i){	char ch=i%10+'0';	s[n]=ch;i/=10;n++;}
		s[n]='\0';
		n--;i=0;
		while(i<n){	char t=s[i];s[i]=s[n];s[n]=t;	n--;i++;}
}
void split(char* temp,char* str[]){
  str[0]=strtok(temp,"$");
  str[1]=strtok(NULL,"$");
}
int main(){
  char wellKnowFifo[]="wellKnowFifo";
  int ret=mkfifo(wellKnowFifo,0777);
  int wellKnowFD=open(wellKnowFifo,O_RDONLY|O_NONBLOCK);
  int fd[100];
  int n=0;
  char temp[100];
  while(1){
    memset(temp,'\0',100);
		int cnt=-1;
		while(cnt==-1||cnt==0)	cnt=read(wellKnowFD,temp,70);
    char *str[2];
    split(temp,str);
    if(atoi(str[0])>100){
      printf("Process %s saying \" %s \" \nGrant Permission?(y/n)\n",str[0],str[1]);
      char ch;
      // scanf(" %c",&ch);
			ch='y';
      if(ch=='n'||ch=='N')  {kill(atoi(str[0]),SIGKILL);continue;}
      mkfifo(str[0],0666);
			fd[n]=open(str[0],O_WRONLY|O_NONBLOCK);
      if(fd[n]==-1){
        kill(atoi(str[0]),SIGKILL);
        perror("Error in creating FIFO \n");
        continue;
      }
      char tt[]={n+'0','\0'};
      write(fd[n],tt,1);
			printf("Granted permission clientno given %d\n",n);
      n++;
    }
    else{
      int j=atoi(str[0]);
			printf("client %s: %s\n",str[0],str[1]);
			char temp2[100];memset(temp2,'\0',100);
			strcpy(temp2,str[0]);strcat(temp2,"$");strcat(temp2,str[1]);
			strcat(temp2,"$");
      for(int i=0;i<n;i++)
        if(j!=i)
          write(fd[i],temp2,strlen(temp2));
    }
  }
}
