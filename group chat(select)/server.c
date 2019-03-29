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

struct msg{
long mtype;
char mtext[200];
};
int isno(char* text)
{
	if(strlen(text)>2)
		return 0;
	int q=(int)text[0]; 
	if(q>60)
		return 0;
	return 1;	
}
int val(char cv)
{
	return ((int)(cv)-48);
}
int whomever(int aa,int* arr,int n)
{
	for(int j=0;j<n;j++)
	{
		if(arr[j]==aa)
			return j;
	}
}
int main(void)
{
	int arr[10];
	int dr[10];
	int e1=0;
        struct my_msgbuf buf;
        int msqid;
        key_t key;

        if ((key = ftok("kirk3s.c", 'B')) == -1)
	 {
            perror("ftok");
            exit(1);
        }

        if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
            perror("msgget");
            exit(1);
        }
        sleep(5);
        for(;;) {
        	printf("Waiting for msgrcv\n");
            if (msgrcv(msqid, (struct msgbuf *)&buf, sizeof(buf), 5, 0) == -1) {
                perror("msgrcv");
                exit(1);
            }
            printf("Done with msgrcv\n");
            printf("Server reading %s\n",buf.mtext);  
            if(isno(buf.mtext))
            {
            	arr[e1]=val(buf.mtext[0]);
            	dr[e1]=val(buf.mtext[1]);
            	e1++;
            }
            else
            {
		printf("Server reading %s\n",buf.mtext);
		printf("Server reading %d\n",strlen(buf.mtext));    
            	int k= buf.mtext[strlen(buf.mtext)-2]-'0';
		printf("K value is %d\n",k);
            	for(int j=0;j<(e1);j++)
            	{
            		if(arr[j]!=k && dr[j]==dr[whomever(k,arr,e1)])
            		{
            			buf.mtype=arr[j];
				if (msgsnd(msqid, (struct msgbuf *)&buf, sizeof(buf), 0) == -1)
					perror("msgsnd2");
				printf("Server writing %s to %d\n",buf.mtext,buf.mtype);  	
            		}
            		
            	}	
            }
            
		sleep(4);
        }

        return 0;
    }
