

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include<poll.h>

struct msg{
  long mtype;
  char mtext[40];
}message;
int msgid=-1;

void init(){
  key_t key=ftok("server1",65);
  int j=key;
  msgid=msgget(key,IPC_CREAT);
  if(msgid<0){perror("Error in creation\n");exit(1);}
  printf("msgid = %d\n",msgid);
}

int main(int argn,char* arg[]){
  int clietno=arg[1][0]-'0';
  clietno--;
  init();
  struct pollfd pfd[1];
  pfd[0].fd=0;pfd[0].events=POLLIN;
  while(1){
    poll(pfd,1,2000);
    if(pfd[0].revents&POLLIN){
      char temp[20];
      scanf("%[^\n]%*c",temp);
      message.mtype=(clietno+1)%3+1;
      // printf("Sended %s\n",message.mtext);
      strcpy(message.mtext,temp);
      int k=msgsnd(msgid,&message,sizeof(message),IPC_NOWAIT);
      if(k==-1){perror("Error Sending message\n");}
    }
    else{
      struct msg tt;
      int f=msgrcv(msgid,&tt,sizeof(tt),clietno+1,IPC_NOWAIT);
      if(f!=-1){
        printf("%s \n",tt.mtext );
      }
    }
  }
}