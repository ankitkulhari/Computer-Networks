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
	char* buff = malloc(100*sizeof(char));
	strcpy(buff,"From Program P5\n");
	while(1)
	{
		write(1,buff,strlen(buff)+1);
		sleep(5);
	}
}
