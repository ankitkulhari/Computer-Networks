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
	//sleep(2);
	while(1)
	{
	
		//printf("Hey2\n");
		char* bufff = malloc(100*sizeof(char));
		int n=100;
		read(0,bufff,n);
		write(1,bufff, strlen(bufff) +1);
		printf("\n");
	}
}
