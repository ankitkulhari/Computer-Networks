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
int main()
{
  char mainfifo[]="wellKnowFifo";
  int ret=mkfifo(mainfifo,0777);
  int wellKnowFD=open(mainfifo,O_RDONLY|O_NONBLOCK);
  int fd[100];
  int n=0;
  char temp[100];
  while(1)
  {
    memset(temp,'\0',100);
		int cnt=-1;
		while(cnt==-1||cnt==0)	
        cnt=read(wellKnowFD,temp,70);

    char* str[2];
    str[0]=strtok(temp,"$");
    str[1]=strtok(NULL,"$");
    if(atoi(str[0])>100)
    {
      mkfifo(str[0],0666);
			fd[n]=open(str[0],O_WRONLY|O_NONBLOCK);
      if(fd[n]==-1)
      {
        perror("Error in creating FIFO \n");
        continue;
      }
      char temparr[2];
      temp[0]=n+'0';
      printf("%c\n",temp[0]);
      temp[1]='\0';
      write(fd[n],temparr,1);
			printf("client added to server %d\n",n);
      n++;
    }
    else
    {
      printf("%s\n",str[0]);
      int j=atoi(str[0]);
			printf("client %s: %s\n",str[0],str[1]);
			// char temp2[100];
   //    memset(temp2,'\0',100);
			// strcpy(temp2,str[0]);
   //    strcat(temp2,"$");
   //    strcat(temp2,str[1]);
			// strcat(temp2,"$");
   //    for(int i=0;i<n;i++)
   //      if(j!=i)
   //        write(fd[i],temp2,strlen(temp2));
    }
  }
}