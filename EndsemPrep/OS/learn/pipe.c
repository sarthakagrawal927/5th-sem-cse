// Hi there
#include <stdlib.h>
#include <stdio.h>
#include  <sys/types.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <ctype.h>
int main(int argc, char const *argv[])
{
    int fd = open("file",O_RDONLY);
    char c;

    while(read(fd, &c,1 ) > 0){
        printf("%c", toupper(c));
    }
    close(fd);
}
