// Hi there
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include<unistd.h>
#include <sys/wait.h>

void handler(int num){
    write(STDOUT_FILENO, "I dont die\n",10);
}

int main(int argc, char const *argv[])
{
    signal(SIGINT, handler); //program won't die on ctrl+c
    // can be killed by kill -TERM PiD
    signal(SIGTERM, handler);
    // no it can't kill

    // only remains kill -KILL Pid

    //sigaction is also an alternative, as its asyncrhonous and better

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
