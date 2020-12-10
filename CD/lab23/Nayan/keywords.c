#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
int main(){
	FILE *fptr;
	int i,j,k;
	char filename[100],c,buff[100],keywords[32][20]={"auto",
	"double",
	"int",
	"struct",
	"break",
	"else",
	"long",
	"switch",
	"case",
	"enum",
	"register",
	"typedef",
	"char",
	"extern",
	"return",
	"union",
	"continue",
	"for",
	"signed",
	"void",
	"do",
	"if",
	"static",
	"while",
	"default",
	"goto",
	"sizeof",
	"volatile",
	"const",
	"float",
	"short",
	"unsigned"};
	printf("enter the input file\n");
	scanf("%s",filename);
	fptr=fopen(filename,"r");
	if(fptr==NULL){
		printf("cannot open file %s",filename);
		exit(0);
	}
	c=fgetc(fptr);
	while(c!=EOF){
       i=0;
       if(isalpha(c)){
       	while(isalpha(c)){
          buff[i++]=c;
          c=fgetc(fptr);
       	}
       	if(!isalnum(c)){
       		buff[i]='\0';
       		//compare
           for(j=0;j<32;j++){
           	if(strcmp(buff,keywords[j])==0){
           		for(k=0;k<buff[k]!='\0';k++){
           			printf("%c",buff[k]>96?buff[k]-32:buff[k]);
           		}
           		printf("\n");
           	}
           }
       	}
       }
       c=fgetc(fptr);
	}
	fclose(fptr);
	return 0;
}