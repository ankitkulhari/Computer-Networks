#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>

struct msg{
  long mtype;
  char mtext[40];
}message;
int msgid=-1;

void init(){
  key_t key=ftok("server",65);
  int j=key;
  msgid=msgget(key,IPC_CREAT);
  if(msgid<0){perror("Error in creation\n");exit(1);}
  printf("msgid = %d\n",msgid);
}

int main(){
  init();
  while(1){
    int f;
    while(f=msgrcv(msgid,&message,sizeof(message),10,IPC_NOWAIT)==-1);
    char temp[100];
    strcpy(temp,message.mtext);
    char* str[2];
    str[0]=strtok(temp,"#");
    str[1]=strtok(NULL,"#");
    printf("Message recievd %s\n",message.mtext);
    if(strcmp(str[1],"destroy")==0){
      printf("Destroying message Queue\n");
      msgctl(msgid,IPC_RMID,NULL);
      exit(0);
    }
    int j=str[0][0]-'0';
    for(int i=1;i<4;i++){
      if(i==j)  continue;
      struct msg tt=message;
      tt.mtype=i;
      int flag=msgsnd(msgid,&tt,sizeof(tt),IPC_NOWAIT);
      if(flag==-1){perror("Error Sending message\n");}
    }
  }
}
