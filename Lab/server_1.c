#include "header.h"

int main(){
    char request[]="abcd";
    int requestfd;
    int flag[2]={0,0};
    int fd[2];
    int ffd[10]={0,0,0,0,0,0,0,0,0,0};
    int fifon[10];
    memset(fifon,0,sizeof(fifon));
    int exitc=0;

    int ret=mkfifo(request,0666);
    if(ret==-1) {
        perror("mkfifo error\n");
    }
    requestfd=open(request,O_RDONLY|O_NONBLOCK);
    char temp[10];
    while(1){
        read(requestfd,temp,5);
        int clientN=temp[0]-'0';
        if(clientN>=0){
            //printf("%s %d \n","client no: ",clientN);
            if(ffd[clientN]==0){
                char s[10]="client";
                char s2[2]={temp[0],'\0'};
                strcat(s,s2);
                int ret=mkfifo(s,0666);
                fifon[clientN]=open(s,O_RDWR|O_NONBLOCK);
                //printf("%s %d\n",s,fifon[clientN]);
            }
            if(temp[1]=='d'&&temp[2]=='1') {
                printf("request for d1\n");
                if(flag[0]==0){
                    flag[0]=1;
                    FILE* ft=popen("./d1","r");
                    fd[0]=fileno(ft);
                    printf("popen d1 %d\n" ,fd[0]);    
                }
              if(ffd[clientN]==0)
                    ffd[clientN]=1;
            }
            else if(temp[1]=='d'&&temp[2]=='2'){
                 printf("request for d2\n");
                if( flag[1]==0){
                    flag[1]=1;
                    FILE* ft=popen("./d2","r");
                    fd[1]=fileno(ft);
                    printf("popen d2 %d\n" ,fd[1]);  
                }
                if(ffd[clientN]==0){
                       ffd[clientN]=2;
                }
            }
        }
        if(flag[0]){
            char str[20];
            printf("Reading from d1\n");
            int cnt=read(fd[0],str,10);
            printf("%s\n",str);
            for(int i=0;i<10;i++)
            	if(cnt==0)	{
            		exitc++;
            	}
                else if(ffd[i]==1){
                    write(fifon[i],str,10);
                }
        }
        if(flag[1]){
            char str[20];
            printf("Reading from d2\n");
            int cnt=read(fd[1],str,10);
            str[11]='\0';
            printf("%s\n",str);
            for(int i=0;i<10;i++)
            	if(cnt==0)	{
            		exitc++;
            	}
                else if(ffd[i]==2){
                    write(fifon[i],str,10);
                }
            if(exitc==2){
            	printf("work completed data center exhausted\n");
            	exit(1);}
        }
        sleep(1);
    }
  }