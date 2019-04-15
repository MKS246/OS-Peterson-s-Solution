# define N 2   
#define   TRUE       1
#define   FALSE      0
#define p0 0
#define p1 1
#include<stdio.h>
#include<pthread.h>
#include <unistd.h>
#include <fcntl.h> 
//int interested[N] = FALSE;  
char buf1[12] = "hello world"; 
char buf2[12] ="bye world";

int fd = open("File.txt", O_RDWR | O_CREAT);
void    BeginSynch(int Thread);
void    EndSynch(int Thread);
void    *p0_write(void *);
void    *p1_write(void *);



int main()
{
	/*turn indicates whose turn it is to enter the crtical ssection
	Flag array is used to indicate if a process is ready to enter the critical 
	section*/
	pthread_t t1; 	//thread of process 1
	pthread_t t2; 	//thread of process 2
	pthread_create(&t1,NULL,p0_write,NULL);	//thread 1 creation
	pthread_create(&t2,NULL,p1_write,NULL);	//thread 2 creation
	pthread_join(t1,NULL);	//joining thread 1
	pthread_join(t2,NULL);	//joining thread 2
	return 0;
}

void *p0_write(void *arg)   {
    
    	int sz;
        BeginSynch(p0);
        sz = write(fd, buf1, strlen(buf1));
        printf("written using p0\n");
        EndSynch(p0);
        
}        
void *p1_write(void *arg)   {
    
    	int sz;
        BeginSynch(p1);
        sz = write(fd, buf2, strlen(buf2));
        printf("written using p1\n");
        EndSynch(p1);
        
}  



int     flag[2];
int     turn;

void BeginSynch(int Thread) {
    int    other = 1 - Thread;  // This is the ID of the other thread
    flag[Thread] = TRUE;
    turn         = other;
    while( flag[other] && (turn == other) ){}
}
void EndSynch(int Thread) {
    flag[Thread] = FALSE;
}
