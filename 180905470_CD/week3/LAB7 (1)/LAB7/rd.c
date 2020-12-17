#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lxa.c"


//prototypes
void declarations();
void assign_stat();
void assign_stat_prime();
void data_type();
void identifier_list();
void identifier_list_prime();
void untoken();
struct token s;

FILE *fa;

void untoken(){
	int len;
	    if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' ')
           len=strlen(s.name)-3;
	    else len=strlen(s.name);
        fseek(fa,-1*len,SEEK_CUR);
}

void Program(){
		s=getnextToken(fa);
		//printf("%s\n",s.name);
		if(strcmp(s.name,"main")==0){
             s=getnextToken(fa);
             if(strcmp(s.name,"(")==0){
                    s=getnextToken(fa);
                    if(strcmp(s.name,")")==0){
                           s=getnextToken(fa);
                           if(strcmp(s.name,"{")==0){
                                 declarations();
                                 assign_stat();
                                 s=getnextToken(fa);
                                  if(strcmp(s.name,"}")==0){
                                          return; 
                                  }
                                  else{
                                  	printf("error: missing '}' row : %d col :%d\n",s.row,s.col);
                                  	exit(1);
                                  }
                           }
                           else{
                           		printf("error: missing '{' row : %d col :%d\n",s.row,s.col);
                           		exit(1);
                           }
                    }
                    else{
                        printf("error: missing ')' row : %d col :%d\n",s.row,s.col);
                        exit(1);
                    }
             }
             else{
             	printf("error: missing '(' row : %d col :%d\n",s.row,s.col);
             	exit(1);
             }
		}
		else{
			printf("missing main row : %d col :%d\n",s.row,s.col);
			exit(1);
		}	

}

void declarations(){
   
	s=getnextToken(fa);
	//printf("dec %s\n",s.name);
	if(strcmp(s.name,"int")==0||strcmp(s.name,"char")==0){
			identifier_list();
	        s=getnextToken(fa);
	        if(strcmp(s.name,";")==0){
		      declarations();
	        }
	        else{
	        	printf("expected ';' row : %d col :%d\n",s.row,s.col);
	        	exit(1);
	        }
	}
    else{
    	untoken();
    }
}

void identifier_list(){
   
     s=getnextToken(fa);
       //printf("id %s\n",s.name);
     if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' '){
           identifier_list_prime();
     }
     else{
     	printf("error : expected identifier row : %d col :%d\n",s.row,s.col);
     	exit(1);
     }

}

void identifier_list_prime(){
     
     s=getnextToken(fa);
      //printf("idprime %s\n",s.name);
     if(strcmp(s.name,",")==0){
           identifier_list();
     }
     else{
        if(strcmp(s.name,";")==0){
     	  untoken();
        }
        else{
      	    printf("error : missing ',' row : %d col : %d\n",s.row,s.col);
     	    exit(1);
      }
     }
     	//printf("error : expecting ',' in line %d\n",s.row);


}

void assign_stat(){
     s=getnextToken(fa);
    // printf("as %s\n",s.name);
     if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' '){
        s=getnextToken(fa);
        if(strcmp(s.name,"=")==0)
     	   assign_stat_prime();
     	else{
     		printf("error : missing '=' row : %d col :%d\n",s.row,s.col);
     	    exit(1);
     	}
     }
     else{
     	printf("error : missing identifier row : %d col :%d\n",s.row,s.col);
        exit(1);
     }

}

void assign_stat_prime(){

     s=getnextToken(fa);
     // printf("aspp %s\n",s.name);
     if((s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' ')||strcmp(s.name,"num")==0){
        s=getnextToken(fa);
        if(strcmp(s.name,";")==0)
     	   return;
     	else{
     		printf("error : missing ';' row : %d col :%d\n",s.row,s.col);
     	    exit(1);
     	}
     }
     else{
     	printf("error : missing identifier or numeric constant row : %d col :%d\n",s.row,s.col);
        exit(1);
     }
}

void data_type(){
	s=getnextToken(fa);
	if(strcmp(s.name,"int")==0||strcmp(s.name,"char")==0)
		return;
	else{
		printf("error : data type not available row : %d col :%d\n",s.row,s.col);
	    exit(1);
	}
}

int main(int argc, char const *argv[])
{
	fa=fopen("abcd.txt","r");
	if(fa==NULL){
		perror("fopen");
		exit(1);
	}
	//Initialize();
	Program();
	s=getnextToken(fa);
	if(strcmp(s.name,"end")==0)
	 printf("*************successfully parsed**************\n");
	//Display();
    

	return 0;
}