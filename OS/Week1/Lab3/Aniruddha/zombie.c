#include <stdlib.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdio.h>


int main() 
{ 
      
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
        
        exit(0); 
    }
  
    return 0; 
} 