#include "header.h"

int main(){
    char f1[]="f2.txt";
    printf("d2 here\n");
    int fd=open(f1,O_RDONLY);
    char str[1001];
    dup2(fd,0);
    char temp[50];
    while(read(0,temp,20)>0)
    {   
       // scanf("%s",temp);
        temp[20]='\0';
        sleep(1);
        write(1,temp,20);
    }
}