#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main()
{
	FILE *fp;
	char filename[100],c,buf[10];
	printf("enter the input file\n");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	if(fp==NULL){
		printf("cannot open file %s",filename);
		exit(0);
	}
    c = fgetc(fp);
while(c!=EOF)
{
int i=0;
buf[0]='\0';
if(c=='=')
{
buf[i++]=c;
c = fgetc(fp);
if(c=='=')
{
buf[i++]=c;
buf[i]='\0';
printf("\n Relational operator : %s",buf);
}
else
{
buf[i]='\0';
printf("\n Assignment operator: %s",buf);
}
}
else
{
if(c=='<'||c=='>'||c=='!')
{
buf[i++]=c;
c = fgetc(fp);
if(c=='=')
{
buf[i++]=c;
}
buf[i]='\0';
printf("\n Relational operator : %s",buf);
}
else
{
buf[i]='\0';
}
}
c = fgetc(fp);
}
fclose(fp);
return 0;
 }