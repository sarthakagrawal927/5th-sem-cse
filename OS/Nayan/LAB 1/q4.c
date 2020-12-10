#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *fa,*fb;
	char c;
	fa = fopen(argv[1],"r");
    fb = fopen(argv[2],"w+");
	c = fgetc(fa);
	while(c!=EOF){
        fputc(c,fb);
        c=fgetc(fa);
	}
	fclose(fa);
	fclose(fb);
	return 0;
}