#include <stdlib.h>
#include <stdio.h>
int main(int argc, char const *argv[])
{
    FILE *f1,*f2;
    f1 = fopen(argv[1],"r");
    f2 = fopen(argv[2],"w");

    char k = fgetc(f1);
    while(k != EOF){
        fputc(k,f2);
        k= fgetc(f1);
    }
   return 0;
}
