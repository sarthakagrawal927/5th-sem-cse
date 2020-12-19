#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
int in,out;
    in = open(argv[1], O_RDONLY);
    out = open(argv[2], O_WRONLY);

    if(argc < 3){
        printf("Insufficient var");
        exit(0);
    }

    if(in == -1){
        printf("File Not found %s\n",argv[1]);
        exit(0);
    }

    if(out == -1){
        printf("File Not found %s\n",argv[2]);
        exit(0);
    }

    int fp = creat("out1.txt",777);

    char c; 
    while(read(in,&c,1 )==1){
        write(out,&c,1);
        write(fp, &c, 1);
    }

    close(in);
    close(out); 
    close(fp);
    return 0;
}
