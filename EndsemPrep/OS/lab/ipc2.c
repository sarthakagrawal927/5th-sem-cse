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

void isPallindrome(int n){
    int rev = 0, rem , orig = n;
   while (n != 0) { 
        rem = n % 10; 
        rev = rev * 10 + rem; 
        n /= 10; 
    } 
     if (orig == rev) 
         printf("Palindrome!\n"); 
     else 
         printf("Not a Palindrome!\n"); 
}
 
int main(int argc, char const *argv[])
{
    int running  =1;
    struct my_msg data;
    int msgid = msgget((key_t)1234 , 0666 | IPC_CREAT);

    if(msgid == -1){
        fprintf(stderr, "message failed");
    }

    int num; 
    int messageToRecieve;
    while(running){

         if(msgrcv(msgid, (void *)&data , sizeof(int), messageToRecieve,0) == -1){
                    fprintf(stderr, "message failed2");
                    exit(EXIT_FAILURE);
        }
        num = data.num;
        if(num == -1){running = 0;             printf("Exiting!\n"); }
        else isPallindrome(num);

        if(msgctl(msgid, IPC_RMID , 0) ==-1){
             fprintf(stderr, "msgctl(IPC_RMID) failed\n"); 
                 exit(EXIT_FAILURE); 
        }
    }
    return 0;
}
