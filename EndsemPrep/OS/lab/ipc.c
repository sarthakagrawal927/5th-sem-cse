#include<stdio.h> 

#include<stdlib.h> 

#include<string.h> 

#include<errno.h> 

#include<unistd.h> 

#include <sys/types.h> 

#include <sys/ipc.h> 

#include <sys/msg.h> 

struct my_msg{
    long int my_msg_type;
    int num;
};

int main(int argc, char const *argv[])
{
    int running  =1;
    int msgid = msgget((key_t)1234 , 0666 | IPC_CREAT);

    if(msgid == -1){
        fprintf(stderr, "message failed");
    }
    struct my_msg data;
    int num; 
    while(running){
        printf("Enter int");
        scanf("%d",&num);
        data.num = num;
        data.my_msg_type = 1;

         if(num == -1)  running = 0;

        else if(msgsnd(msgid, (void *)&data , sizeof(int),0) == -1){
             fprintf(stderr, "message failed2");
             exit(EXIT_FAILURE);
        }
    }
    return 0;
}
