#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>

// the zombie will be adopted by init 
int main() 
{ 
    char *command = "pstree -p ";
    // Fork returns process id 
    // in parent process 
    pid_t child_pid = fork(); 
  
    // Parent process  
    if (child_pid > 0) {
        printf(" i am PARENT , PID: %d\n",getpid() );
        sleep(5); 
    }
  
    // Child process 
    else{    
        printf(" i am CHILD , PID: %d\n",getpid() );
        printf(" current parent of child , PID: %d\n",getppid() );
        sleep(6);
        printf(" current parent of child , PID: %d\n",getppid() );
        char buf[32];
        // sprintf(pid, "%d", getppid());
        // execl("/bin/pstree", "pstree", "-p", pid, (char*)0);
        sprintf(buf,"pstree -p %d",getppid());
        printf(" parent of %d is %d \n",getppid(),system(buf) );
        sleep(1);
        exit(0); 
    }
  
    return 0; 
} 