#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    if(argc <2){
        printf("Insufficient arguments");
        exit(0);
    }
    int line = 1;
    for(int i = 1; i < argc; i++){
        int f = open(argv[i], O_RDONLY);
        if(f == -1){
            printf("FIle not found");
            exit(0);
        }
        char c = ' ';
        char sentence[200]; 
        int s = 0;
        while(read(f,&c,1) == 1){
            if(c == '\n'){
                printf("%s\n",sentence);
                for(int i = 0; i <s; i++) sentence[i] = 0;
                s=0;
                line++;
            }
            sentence[s++] = c;
            if(line%20 == 0 ) {
                getchar(); 
                line = 1;
            }
        }
        close(f);
    }
    return 0;
}
