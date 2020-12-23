// Hi there
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include<unistd.h>
#include <stdint.h>
#include <sys/mman.h>

#define PAGESIZE 4096
int v =12;

int main(int argc, char const *argv[])
{
    u_int8_t *shared_memory = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, 
                                                          MAP_SHARED | MAP_ANONYMOUS , -1,0  );
    *shared_memory = 40;
    if(  fork() == 0){
        *shared_memory = 80;
        printf("%d\n",*shared_memory);
    }
    else{ 
printf("%d\n",*shared_memory);        }
    return 0;
}

