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
	int fd1,fd2,fd5;
	pid_t p,c[3];
	fd1 = fileno(popen("./vo1","r"));
	dup2(fd1,0);
	fd2 = fileno(popen("./vo2","r"));
	fd5 = fileno(popen("./vo3","w"));
	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[1].fd = fd2;
	fds[0].events = POLLRDNORM | POLLRDBAND;	
	fds[1].events = POLLRDNORM | POLLRDBAND;
	char* buff1 = malloc(10*sizeof(char));
	int n1=10;
	char* buff2 = malloc(10*sizeof(char));
	int n2=10;
	int s;
	while(1)
	{
		s = poll(fds, 2, 500);
		if(s>0)
		{
			if((fds[0].revents & POLLRDNORM) || (fds[0].revents & POLLRDBAND))
			{
				
				read(0, buff1, 10);
				write(fd5, buff1 , strlen(buff1) +1 );
			}
			if((fds[1].revents & POLLRDNORM) || (fds[1].revents & POLLRDBAND))
			{
				
				read(fd2, buff2, 10);
				write(1, buff2 , strlen(buff2) +1 );
				
			}
		}
	}
}
