#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fa,*fb;
	char filename[100],ca,cb;
	printf("enter the input file\n");
	scanf("%s",filename);
	fa=fopen(filename,"r");
	if(fa==NULL){
		printf("cannot open file %s",filename);
		exit(0);
	}
	printf("enter the output file\n");
	scanf("%s",filename);
	fb=fopen(filename,"w+");
	ca=fgetc(fa);
    while (ca != EOF)
{
if(ca==' ')
{
putc(ca,fb);
while(ca==' ')
ca = getc(fa);
}
if (ca=='/')
{
    cb = getc(fa);
    if (cb == '/')
    {
        while(ca != '\n')
            ca = getc(fa);
    }
else if (cb == '*')
{
    do
    {
    while(ca != '*')
        ca = getc(fa);
        ca = getc(fa);
    } while (ca != '/');
}
else
{
    putc(ca,fb);
    putc(cb,fb);
}

}
else
 putc(ca,fb);
 
 ca = getc(fa);
}
fclose(fa);
fclose(fb);
return 0;
}