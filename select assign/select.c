#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <poll.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
int main()
{
	fd_set rfds;
    	struct timeval tv;
    	int fd1,fd2,fd3,fd4,fd5,fd6;
	FILE* fdd1;
	FILE* fdd2;
	FILE* fdd3;
	FILE* fdd4;
	FILE* fdd5;
	fdd1=popen("./v1","r");
	fdd2=popen("./v2","r");
	fdd3=popen("./v3","r");
	fdd4=popen("./v4","r");
	fdd5=popen("./v5","w");
	
	fd1=fileno(fdd1);
	fd2=fileno(fdd2);
	fd3=fileno(fdd3);
	fd4=fileno(fdd4);
	fd5=fileno(fdd5);

	FD_ZERO(&rfds);
    	FD_SET(fd1,&rfds);
    	FD_SET(fd2,&rfds);
    	FD_SET(fd3,&rfds);
    	FD_SET(fd4,&rfds);

    	printf("%d %d %d %d %d\n",fd2,fd3,fd4,fd5,fd6);
	tv.tv_sec=1;
    	tv.tv_usec=0;
    	int n1=30;
    	char buff1[30];

	while(1)
	{
		memset((void *)buff1,0,11);
		tv.tv_sec = 1;
    		tv.tv_usec = 0;
		FD_SET(fd1,&rfds);
	    	FD_SET(fd2,&rfds);
	    	FD_SET(fd3,&rfds);
	    	FD_SET(fd4,&rfds);
		retval = select(9, &rfds, NULL, NULL, &tv);
		printf("No of Available: %d\n",retval);
		if(retval>0)
		{
			if(FD_ISSET(fd1, &rfds))
			{
				buff1[0]='\0';
				read( fileno(fdd1),buff1, n1);
				fputs(buff1,fdd5);
				fflush(fdd5);
			}
			if(FD_ISSET(fd2, &rfds))
			{
				
				buff1[0]='\0';
				read( fileno(fdd2),buff1, n1);
				fputs(buff1, fdd5);
				fflush(fdd5);
			}
			if(FD_ISSET(fd3,&rfds))
			{
				buff1[0]='\0';
				read( fileno(fdd3),buff1, n1);
				fputs(buff1, fdd5);
				fflush(fdd5);
			}
			if(FD_ISSET(fd4, &rfds))
			{
				
				buff1[0]='\0';
				read( fileno(fdd4),buff1, n1);
				fputs(buff1, fdd5);
				fflush(fdd5);
				
			}
		}
		else
		{
			printf("No one is ready\n");			
			int br=read( 0,buff1, n1);
			buff1[br]='\0';
			write(fileno(fdd5),buff1,strlen(buff1)+1);
		}
		printf("No of Aailable: %d\n",retval);
		sleep(2);
	}
}
