#include "header.h"

int main(){

	char request[]="abcd";
	int fd=open(request,O_WRONLY);
	printf("Enter data center from which it will read\n");
	char temp[10];
	scanf("%s",temp);
	write(fd,temp,10);
	char s1[]="client";
	char s2[]={temp[0],'\0'};
	strcat(s1,s2);
	sleep(2);
	int ret=mkfifo(s1,0666);
	int fifofile=open(s1,O_RDONLY|O_NONBLOCK);
	
	printf("%s %d\n Reading \n",s1,fifofile);
	sleep(2);
	while(read(fifofile,temp,10)>0){
		sleep(1);
		printf("%s\n",temp);
	}
}
