#include<stdio.h> 

#include<stdlib.h> 

#include<string.h> 

#include<errno.h> 

#include<unistd.h> 

#include <sys/types.h> 

#include <sys/ipc.h> 

#include <sys/msg.h> 

  

#define MAX_TEXT 512 

  

struct my_msg{ 

    long int my_msg_type; 

    int num; 

}; 

  

int main(int argc, char const *argv[]) 

{ 

    int running = 1; 

    struct my_msg some_data; 

    int msgid; 

    char buffer[BUFSIZ]; 

  

    msgid = msgget((key_t) 1234, 0666 | IPC_CREAT); 

  

    if(msgid == -1){ 

        fprintf(stderr, "mssget failed with error: %d\n", errno); 

        exit(EXIT_FAILURE); 

    } 

  

    int num; 

    while(running){ 

        printf("Enter an integer(-1 to exit):"); 

        scanf("%d", &num); 

  

        some_data.my_msg_type = 1; 

        some_data.num = num; 

  

        if(msgsnd(msgid, (void*)& some_data, sizeof(int), 0) == -1){ 

            fprintf(stderr, "msgsnd failed with error:%d\n", errno); 

            exit(EXIT_FAILURE); 

        } 

  

        if(num == -1) 

            running = 0; 

    } 

  

    exit(EXIT_SUCCESS); 

    return 0; 

} 