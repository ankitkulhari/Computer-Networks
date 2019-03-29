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
	while(1)
	{
		char* bufff = malloc(10*sizeof(char));
		int n=10;
		read(0,bufff,n);
		write(1,bufff, strlen(bufff) +1);
		
		sleep(2);
	}
}
