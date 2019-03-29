#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h>
#include<poll.h>


struct msg{
  long mtype;
  char mtext[40];
}message;
int msgid=-1,clientNo=-1;

void init(){
  key_t key=ftok("server",65);
  msgid=msgget(key,IPC_CREAT);
  if(msgid<0){perror("Error in creation\n");exit(1);}
  printf("msgid = %d\n",msgid);
}

int main(int argn,char* arg[]){
  init();
  clientNo=arg[1][0]-'0';
  printf("ClientNo %d\n",clientNo);
  struct pollfd pfd[1];
  pfd[0].fd=0;pfd[0].events=POLLIN;
  while(1){
    poll(pfd,1,2000);
    if(pfd[0].revents&POLLIN){
      char temp[20];
      scanf("%[^\n]%*c",temp);
      message.mtype=10;
      message.mtext[0]=clientNo+'0';message.mtext[1]='#';message.mtext[2]='\0';
      strcat(message.mtext,temp);strcat(message.mtext,"#");
      // printf("Sended %s\n",message.mtext);

      int k=msgsnd(msgid,&message,sizeof(message),IPC_NOWAIT);
      if(k==-1){perror("Error Sending message\n");}
    }
    else{
      struct msg tt;
      int f=msgrcv(msgid,&tt,sizeof(tt),clientNo,IPC_NOWAIT);
      if(f!=-1){
        char* str[2]={strtok(tt.mtext,"#"),strtok(NULL,"#")};
        printf("Client %s: %s\n",str[0],str[1]);
      }
    }
  }
}