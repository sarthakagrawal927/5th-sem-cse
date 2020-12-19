#include<stdio.h> 

#include<stdlib.h> 

#include<string.h> 

#include<errno.h> 

#include<unistd.h> 

#include <sys/types.h> 

#include <sys/ipc.h> 

#include <sys/msg.h> 

#include<stdbool.h> 

struct my_msg{ 

    long int my_msg_type; 

    int num; 

}; 

  

void isPalindrome(int n){ 

    int reversedN = 0, remainder; 

    int originalN = n; 

  

    while (n != 0) { 

        remainder = n % 10; 

        reversedN = reversedN * 10 + remainder; 

        n /= 10; 

    } 

  

     if (originalN == reversedN) 

         printf("Palindrome!\n"); 

     else 

         printf("Not a Palindrome!\n"); 

  

    return; 

} 

  

int main(int argc, char const *argv[]) 

{ 

    int running = 1; 

    int msgid; 

    struct my_msg some_data; 

    long int msgToRecieve = 0; 

  

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT); 

  

    if(msgid == -1){ 

        fprintf(stderr, "mssget failed with error: %d\n", errno); 

        exit(EXIT_FAILURE); 

    } 

  

    int num; 

    while(running){ 

        if(msgrcv(msgid, (void*)& some_data, sizeof(int), msgToRecieve, 0) == -1){ 

            fprintf(stderr, "msgrcv failed with error:%d\n", errno); 

            exit(EXIT_FAILURE); 

        } 

  

        // printf("You wrote: %s", some_data.buffer); 

        num = some_data.num; 

         

        if(num == -1){ 

            running = 0; 

            printf("Exiting!\n"); 

        } 

        else 

            isPalindrome(num); 

    } 

  

    if(msgctl(msgid, IPC_RMID, 0) == -1){ 

        fprintf(stderr, "msgctl(IPC_RMID) failed\n"); 

        exit(EXIT_FAILURE); 

    } 

  

    exit(EXIT_SUCCESS); 

    return 0; 

} 