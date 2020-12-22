// Hi there
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
    if(  fork() == 0){
        printf("ch");
        execlp("ls","ls","-al",NULL);  //doesn't execute anything after this
        printf("Hello");
    }
    // basically clones the process  as child
    else printf("SS from %d\n",getpid());
    return 0;
}

/*
should also have null in the end , to mark the end
exec
        v  - vector
        or
        l  -  list
                p  - look at the path program (makes things easier)
                        e -  pass different set of var
*/