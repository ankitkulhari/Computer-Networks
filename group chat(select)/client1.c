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
#include<string.h>
#include<errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <poll.h>
#include <sys/time.h>
#include <sys/select.h>
struct my_msgbuf {
long mtype;
char mtext[200];
};

int main(void)
{
	fd_set rfds;
    	struct timeval tv;
    	int retval;
    	FD_ZERO(&rfds);
    	FD_SET(0, &rfds);
    	
    	tv.tv_sec = 1;
    	tv.tv_usec = 0;
        struct my_msgbuf buf,buf1;
        buf.mtype=5;
        strcpy(buf.mtext,"11");
        int msqid;
        key_t key;

        if ((key = ftok("kirk3s.c", 'B')) == -1) {
            perror("ftok");
            exit(1);
        }

        if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
            perror("msgget");
            exit(1);
        }
        if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1) {
                perror("msgsnd");
                exit(1);
            }
        sleep(2);    
        char* buff1 = malloc(100*sizeof(char));
	int n1=10;
	strcpy(buf.mtext,"Hi I am CLient 1");
	if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1) {
			perror("msgsnd");
			exit(1);
		    }	 
        while(1) {
        	tv.tv_sec = 1;
    		tv.tv_usec = 0;
		FD_SET(0, &rfds);
		retval = select(2, &rfds, NULL, NULL, &tv);
		printf("retval: %d\n",retval);
 	    if(retval)
 	    {
 	    	
		buff1[0]='\0';
		read(0,buff1, n1);
		strcpy(buf.mtext,buff1);
		if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1) {
			perror("msgsnd");
			exit(1);
		    }	 
 	    }	         
 	    sleep(3);
 	    if (msgrcv(msqid, (struct msgbuf *)&buf1, sizeof(buf1),1, 0) == -1)
		        perror("msgrcv");
	    printf("Client 1 reading %s\n",buf1.mtext);  
        }

        return 0;
    }
