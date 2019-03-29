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
int main()
{
	FILE* fd2;
	FILE* fd3;
	FILE* fd4;
	FILE* fd5;
	FILE* fd6;
	fd2 = popen("./ve2","r");
	fd3 = popen("./ve3","r");
	fd4 = popen("./ve4","r");
	fd5 = popen("./ve5","r");
	fd6 = popen("./ve6","w");
	struct pollfd fds[4];
	fds[0].fd = fileno(fd2);
	fds[1].fd = fileno(fd3);
	fds[2].fd = fileno(fd4);
	fds[3].fd = fileno(fd5);
	fds[0].events = POLLRDNORM | POLLRDBAND;	
	fds[1].events = POLLRDNORM | POLLRDBAND;
	fds[2].events = POLLRDNORM | POLLRDBAND;	
	fds[3].events = POLLRDNORM | POLLRDBAND;
	char* buff1 = malloc(100*sizeof(char));
	char* ibuff = malloc(100*sizeof(char));
	strcpy(ibuff,"From P1 \n");
	int n1=100;
	int s;
	while(1)
	{
		s = poll(fds, 4 , 500);
		if(s>0)
		{
			if((fds[0].revents & POLLRDNORM) || (fds[0].revents & POLLRDBAND))
			{
				buff1[0]='\0';
				read( fileno(fd2),buff1, n1);
				write(fileno(fd6),buff1,strlen(buff1)+1);
			}
			else if((fds[1].revents & POLLRDNORM) || (fds[1].revents & POLLRDBAND))
			{
				buff1[0]='\0';
				read( fileno(fd3),buff1, n1);
				write(fileno(fd6),buff1,strlen(buff1)+1);
			}
			else if((fds[2].revents & POLLRDNORM) || (fds[2].revents & POLLRDBAND))
			{
				buff1[0]='\0';
				read( fileno(fd4),buff1, n1);
				write(fileno(fd6),buff1,strlen(buff1)+1);
			}
			else if((fds[3].revents & POLLRDNORM) || (fds[3].revents & POLLRDBAND))
			{
				buff1[0]='\0';
				read( fileno(fd5),buff1, n1);
				write(fileno(fd6),buff1,strlen(buff1)+1);
			}
			
		}
		else
		{
			write(fileno(fd6),ibuff,strlen(ibuff)+1);
		}
	sleep(3);
	}
}
