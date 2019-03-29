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
	char* buff5 = malloc(10*sizeof(char));
	strcpy(buff5,"Hillo\n");
	while(1)
	{
		write(1,buff5,strlen(buff5)+1);
		sleep(5);
	}
}
