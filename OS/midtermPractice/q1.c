#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    if(argc < 3){
        printf("Insufficient arguments");
        exit(0);
    }
    int f = open(argv[1], O_RDONLY);
    if(f == -1){
        printf("FIle not found");
        exit(0);
    }
    char c;
    char sentence[100]; int s = 0;
    while(read(f,&c,1) == 1){
        if(c == '\n'){
            if(strstr(sentence,argv[2])) printf("%s\n",sentence);
            for(int i = 0; i <s; i++) sentence[i] = 0;
            s=0;
        }
        sentence[s++] = c;
    }
    close(f);
    return 0;
}
