#include <stdlib.h> 

#include <stdio.h> 

#include <string.h> 

#include <errno.h> 

#include <unistd.h> 

#include <sys/types.h> 

#include <sys/ipc.h> 

#include <sys/shm.h> 

  
struct shared_use 

{ 

    char c; 

    char next_char; 

}; 

  

int main() 

{ 

    int running = 1; 

    pid_t pid; 

    void *shared_memory = (void *)0; 

    int shmid; 

    struct shared_use *st; 

    srand((unsigned int)getpid()); 

    shmid = shmget((key_t)1234,sizeof(struct shared_use),0666|IPC_CREAT); 

    if(shmid==-1) 

    { 

        fprintf(stderr,"shmget failed\n"); 

        exit(EXIT_FAILURE); 

    } 

    shared_memory = shmat(shmid,(void *)0,0); 

    if(shared_memory == (void *)-1) 

    { 

        fprintf(stderr, "shmat failed\n"); 

        exit(EXIT_FAILURE); 

    } 

    st = (struct shared_use *)shared_memory; 

    char ch; 

    printf("Enter a character: \n"); 

    scanf("%c",&ch); 

    st->c=ch; 

    printf("You entered: %c\n",st->c); 

  

    pid = fork(); 

    if(pid == -1) 

    { 

        fprintf(stderr, "%d\n",errno); 

        exit(1); 

    } 

    else if(pid == 0) 

    { 

        //Child process 

        printf("Current character: %c\n",st->c); 

        st->c++;     

    } 

    else 

    { 

        //Parent process 

        printf("\nWaiting for Child process to increment the character\n"); 

        sleep(2); 

        printf("Updated character: %c\n",st->c); 

    } 

    if(shmdt(shared_memory)==-1) 

    { 

        fprintf(stderr, "shmdt failed\n"); 

        exit(EXIT_FAILURE); 

    } 

} 

 