// Hi there
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
   while(1){
       if(fork() == 0){ // this program creates zombies  , which are not killed
           printf("Child : %d\n",getpid());
           return 0;
       }
       else{
           wait(NULL); // the zombie killer, makes sure the last process is dies
           printf("parent won't die\n");
           sleep(4);
       }
   }
    return 0;
}
