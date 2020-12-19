#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#define sz 30

struct token{
  char name[20];
  int row,col;
};

int row=1,col=1;
//bool filenotended=true;

char keyword[35][10]={"printf","scanf","auto","double","int",

"struct","break","else","long","switch","case","enum","register",

"typedef","char","extern","return","union","continue",

"for","signed","void","do","if","static","while","default","goto",

"sizeof","volatile","const","float","short","unsigned"};


bool iskeyword(char* buf){
   for(int i=0;i<35;i++){
   	 if(strcmp(keyword[i],buf)==0)
   	 	return true;
   }
   return false;
}

bool isDelimiter(char ch){
	 if (ch == ',' || ch == ';'  || ch == '(' || ch == ')' || ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return true;
    return false;
}

bool isArithmetic_operator(char ch)
{
    if (ch == '%' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' )
        return true;
    return false;
}

void printtok(struct token t){
   printf("<%s,%d,%d> ",t.name,t.row,t.col-1);
}

struct token getnextToken(FILE *fa){
    char ca,cb;
    int i,j;
    char buf[sz],temp[sz];
    struct token s;
    ca=fgetc(fa);
    while(ca!=EOF){
    	//newline
    	if(ca=='\n'){
    		row++;
    		col=1;
    		//printf("\n");
    	}
    	//blank space and tabs
    	else if(ca==' '||ca=='\t'){
    		  col++;//doubt
              while(ca==' '||ca=='\t')
                   ca=fgetc(fa);
              fseek(fa,-1,SEEK_CUR);
    	}
        //comments
        else if(ca=='/'){
            col++;
        	cb=fgetc(fa);
        	if(cb=='/'){
                 while(ca!='\n')
                  ca=fgetc(fa);
                 fseek(fa,-1,SEEK_CUR);
        	}
        	else if(cb=='*'){
                    do{
                    	while(ca!='*')
                    		ca = fgetc(fa);
                    	ca = fgetc(fa);
                    }while(ca!='/');
        	}
        	else{
        		i=0;
                while(ca!='\n'){
                	temp[i++] = ca;
                	ca = fgetc(fa);
                }
                 temp[i]='\0';
                 strcpy(s.name,"syntax error");
                 s.row=row;
                 s.col=col;
                 fseek(fa,-1,SEEK_CUR);
                 return s;
        	}
        }
        //preprocessor
        else if(ca=='#'){
        	i=0;
            while(ca!='\n'){
        	 temp[i++]=ca;
        	 ca=fgetc(fa);
            }
            temp[i]='\0';
            fseek(fa,-1,SEEK_CUR);
            if(strstr(temp,"#include")==NULL && strstr(temp,"#define")==NULL){//not working
                 printf("include\n");
            	 strcpy(s.name,"syntax error");
                 s.row=row;
                 row++;
                 s.col=col;
                 return s;
            }
        }
        //keywords and identifiers
        else if(isalpha(ca)||ca=='_'){
        	i=0;
        	while(isalnum(ca)||ca=='_'){
               buf[i++]=ca;
               ca=fgetc(fa);
               col++;
        	}
        	buf[i]='\0';
        	fseek(fa,-1,SEEK_CUR);

        	if(iskeyword(buf)){
                 strcpy(s.name,buf);
                 s.row=row;
                 s.col=col-strlen(buf)+1;
                 return s;
        	}
        	else{
                strcpy(s.name,"id");
                 s.row=row;
                 s.col=col-strlen(buf)+1;
                 return s;
        	}
        }
        //relational operator
        else if(ca=='='||ca=='>'||ca=='<'||ca=='!'){
        	cb=fgetc(fa);
        	i=0;
        	temp[i++]=ca;
            col++;
        	if(cb=='='){
                 temp[i++] = cb;
                 temp[i] = '\0';
                 strcpy(s.name,temp);
                 s.row=row;
                 s.col=col;
                 col++;
                 return s;
        	}
        	else{
                    temp[i]='\0';
                    strcpy(s.name,temp);
                 	s.row=row;
                 	s.col=col;
                    fseek(fa,-1,SEEK_CUR);
                 	return s;
        	}

        }
        //string
        else if(ca=='"'){
        	 i=0;
             do{
             	col++;
             	i++;
             	ca=fgetc(fa);
             }while(ca!='"');
             col++;
             strcpy(s.name,"string literal");
                 	s.row=row;
                 	s.col=col-i;
                 	return s;
        }
        //delimiters
        else if(isDelimiter(ca)){
        	 i=0;
        	 temp[i++]=ca;
        	 temp[i]='\0';
        	 col++;
             strcpy(s.name,temp);
                 	s.row=row;
                 	s.col=col;
                 	return s;
        }
        //numeric constants
        else if(isdigit(ca)){
        	i=0;
        	while(isdigit(ca)){
        		col++;
        		i++;
        		ca=fgetc(fa);
        	}
        	fseek(fa,-1,SEEK_CUR);
        	strcpy(s.name,"num");
                 	s.row=row;
                 	s.col=col-i+1;
                 	return s;
        }
        //arithmetic op
        else if(isArithmetic_operator(ca)){
        	 i=0;
        	 temp[i++]=ca;
        	 temp[i]='\0';
        	 col++;
             strcpy(s.name,temp);
                 	s.row=row;
                 	s.col=col;
                 	return s;
        }
        ca=fgetc(fa);
    }
    //filenotended=false;
    //exit(0);
    return s;
}

// int main(int argc, char const *argv[])
// {
// 	FILE *fa;
// 	fa=fopen("abc.txt","r");
// 	if(fa==NULL){
// 	   perror("fopen");
// 	   exit(1);
// 	}
//     char c=fgetc(fa);
//     row=1;
//     col=1;
//     struct token t;
//     while(filenotended){
//           t=getnextToken(fa);
//           printtok(t);
//     }
//     fclose(fa);
// 	return 0;
// }
