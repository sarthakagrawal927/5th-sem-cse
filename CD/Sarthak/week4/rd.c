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
void identifier_list_prime_prime();
void statement();
void statement_list();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void relop_prime();
void addop();
void mulop();

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
                                 statement_list();
                                  s=getnextToken(fa);
                                  if(strcmp(s.name,"}")==0){
                                          return; 
                                  }
                                  else{
                                  	printf("error: missing '}' at line %d\n",s.row);
                                    exit(1);
                                  }
                           }
                           else{
                           		printf("error: missing '{' at line %d\n",s.row);
                              exit(1);
                           }
                    }
                    else{
                        printf("error: missing ')' at line %d\n",s.row);
                        exit(1);
                    }
             }
             else{
             	printf("error: missing '(' at line %d\n",s.row);
              exit(1);
             }
		}
		else{
			printf("missing main in line %d\n",s.row);
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
	        	printf("expected ';' at line %d\n",s.row );
            exit(1);
	        }
	}
    else{
    	untoken();
    	//assign_stat();//doubt
    }
}

void identifier_list(){
   
     s=getnextToken(fa);
       //printf("id %s\n",s.name);
     if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' '){
           identifier_list_prime();
     }
     else{
     	printf("error : expected identifier ar line %d",s.row);
      exit(1);
     }

}

void identifier_list_prime(){
     
     s=getnextToken(fa);
     // printf("idprime %s\n",s.name);
     if(strcmp(s.name,",")==0){
           identifier_list();
     }
     else if(strcmp(s.name,"[")==0){
           identifier_list_prime_prime();
     }
     else{
       untoken();
     }
     	//printf("error : expecting ',' in line %d\n",s.row);


}

void identifier_list_prime_prime(){
     s=getnextToken(fa);
     if(strcmp(s.name,"num")==0){
          s=getnextToken(fa);
          if(strcmp(s.name,"]")==0){
              s=getnextToken(fa);
              if(strcmp(s.name,",")==0)
                    identifier_list();
              else{
                 untoken();
              }    
          }
          else{
            printf("error: expected ']' in line %d\n",s.row);
            exit(1);
          }
     }
}

void statement_list(){
  s=getnextToken(fa);
  if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' '){
        untoken();
        statement();
        statement_list();
     }
    else
      untoken();
}

void statement(){
  assign_stat();
  s=getnextToken(fa);
  if(strcmp(s.name,";")!=0){
    printf("error expecting ';' row %d col %d\n",s.row,s.col);
    exit(1);
  }
}


void assign_stat(){
     
     s=getnextToken(fa);
    // printf("as %s\n",s.name);
     if(s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' '){
        s=getnextToken(fa);
        if(strcmp(s.name,"=")==0)
     	   expn();
     	else{
     		printf("error : missing '=' in line %d\n",s.row);
        exit(1);
      }
     }
     else{
     	printf("error : missing identifier in line %d\n",s.row);
      exit(1);
     }
}

void expn(){
   simple_exp();
   eprime();
}

void eprime(){
  s=getnextToken(fa);
  if(strcmp(s.name,"==")==0||strcmp(s.name,"!=")==0||strcmp(s.name,"<=")==0||strcmp(s.name,">=")==0||strcmp(s.name,"<")==0||strcmp(s.name,">")==0){
    untoken();
    relop();
    simple_exp();
  }
  else
    untoken();
}

void simple_exp(){
  term();
  seprime();
}

void seprime(){
  s=getnextToken(fa);
  if(strcmp(s.name,"+")==0||strcmp(s.name,"-")==0){
     untoken();
     addop();
     term();
     seprime();
  }
  else
    untoken(); 

}

void term(){
  factor();
  tprime();
}


void tprime(){
  s=getnextToken(fa);
  if(strcmp(s.name,"*")==0||strcmp(s.name,"/")==0||strcmp(s.name,"%")==0){
     untoken();
     mulop();
     factor();
     tprime();
  }
  else
    untoken(); 
}

void factor(){
  s=getnextToken(fa);
   if((s.name[0]=='i'&&s.name[1]=='d'&&s.name[2]==' ')||strcmp(s.name,"num")==0){
       return;
   }
   else{
    printf("error : expected id or num in line %d\n",s.row);
    exit(1);
  }
}

void relop(){
  s=getnextToken(fa);
  if(strcmp(s.name,"==")==0||strcmp(s.name,"!=")==0||strcmp(s.name,"<=")==0||strcmp(s.name,">=")==0||strcmp(s.name,"<")==0||strcmp(s.name,">")==0){
    return;
  }
  else{
    printf("error: expected relational operator in line %d \n",s.row);
    exit(1);
  }
}

void addop(){
  s=getnextToken(fa);
  if(strcmp(s.name,"+")==0||strcmp(s.name,"-")==0){
    return;
  }
  else{
     printf("error: expected + or - operator in line %d \n",s.row);
     exit(1);
  }
}

void mulop(){
  s=getnextToken(fa);
  if(strcmp(s.name,"*")==0||strcmp(s.name,"/")==0||strcmp(s.name,"%")==0){
    return;
  }
  else{
     printf("error: expected * or / or %% operator in line %d \n",s.row);
     exit(1);
  }
}


int main(int argc, char const *argv[])
{
	fa=fopen("abc.txt","r");
	if(fa==NULL){
		perror("fopen");
		exit(1);
	}
	  Program();
    s=getnextToken(fa);
    if(strcmp(s.name,"end")==0)
    printf("*****successfully parsed*******\n");

	return 0;
}