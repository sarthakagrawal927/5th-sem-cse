#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *fptr1,*fptr2;
	char filename[100],c;
	printf("enter the input file\n");
	scanf("%s",filename);
	fptr1=fopen(filename,"r");
	if(fptr1==NULL){
		printf("cannot open file %s",filename);
		exit(0);
	}
	printf("enter the output file\n");
	scanf("%s",filename);
	fptr2=fopen(filename,"w+");
	c=fgetc(fptr1);
	while(c!=EOF){
		    if(c==' '||c=='\t'){
		      fputc(' ',fptr2);
		      c=fgetc(fptr1);
			  while(c==' '||c=='\t'){
					c=fgetc(fptr1);
			  }
			  fputc(c,fptr2);
			}
			else
			 fputc(c,fptr2);
			c=fgetc(fptr1);
	}
	fclose(fptr1);
	fclose(fptr2);
	return 0;
}