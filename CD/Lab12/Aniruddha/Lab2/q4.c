#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

bool FILE_NOT_ENDED = true;

// int token_type[10][10] = {{"id"},{"num"}};

char buf [100];

char temp[100],word[100],digit[100];

char keywords[10][10] ={{"IF"},{"ELSE"},{"INT"},{"RETURN"},{"PRINTF"}};

char delimiters[5] = {'(',')','{','}',';'};

char rela_op[10][10] = {{">="},{"<="},{"=="}};

int row=0,col=0;

bool is_keyword(){
	// printf(" %s \n", word );
	for(int i=0;i<5;++i){
		if( strcmp(word,keywords[i])==0 ){
			return true;
		}
	}
	return false;
}

int is_delimiter(char ch){
	// printf(" %s \n", word );
	for(int i=0;i<5;++i){
		if( ch == delimiters[i] ){
			return i;
		}
	}
	return -1;
}


bool is_include(){
	char s[] = "#include";
	for(int i=0;i<8;++i){
		if(s[i]!=temp[i]){
			return false;
		}
	}
	return true;
}

bool is_define(){
	char s[] = "#define";
	for(int i=0;i<7;++i){
		if(s[i]!=temp[i]){
			return false;
		}
	}
	return true;
}

void getNextToken(FILE *fa,FILE *fb){
	char ca,cb;
	ca = getc(fa); ++col;
	while(ca!=EOF){

		// remove preprocessor

		if(ca=='\n') {
			++row; col=0;
		}

		if(ca=='#'){
			// putc(ca,fb);
			int x=0;
			while(ca!='\n'){

				// ca = getc(fa);
				temp[x++] = ca;
				temp[x] = '\0';
				ca = getc(fa); ++col;
			}
			
			// printf(" bool = %d \n",is_include() );
			if(!is_include() && !is_define() ){
				for(int k=0;k<x;++k){
					putc(temp[k],fb);
				}
				printf("< %s ,%d ,%d > \n", "id",row,col );
			}
			++row; col=0;
		}

		// remove comments , blankspaces
		if(ca==' '){
			putc(ca,fb);
			while(ca==' '){
				ca = getc(fa); ++col;
			}
		}
		if (ca=='/'){
			cb = getc(fa); ++col;
			if (cb == '/'){
				while(ca != '\n')
					ca = getc(fa); ++col;
				++row; col =0;
			}
			else if (cb == '*'){
				do{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				}while (ca != '/');
			}
			else{
				fseek(fa, -2, SEEK_CUR);
			}
		}
		
		// check for keywords
		if( isalpha(ca)  ){
			int x=0;
			while(isalpha(ca)){
				word[x++] = (char)toupper(ca);
				word[x] = '\0';
				ca = getc(fa); ++col;
			}
			if( is_keyword() ){
				printf("< %s ,%d ,%d > \n", word,row,col-x );
			}
			else{
				printf("< %s ,%d ,%d > \n", "id",row,col-x );
			}

		}

		// check for delimiters
		if( ( is_delimiter(ca) ) >= 0 ){
			printf("< %c ,%d ,%d > \n", delimiters[is_delimiter(ca)],row,col );
		}

		// check for digits
		if( isdigit(ca)  ){
			int x=0;
			while(isdigit(ca)){
				digit[x++] = (char)toupper(ca);
				digit[x] = '\0';
				ca = getc(fa); ++col;
			}
			
			printf("< %s ,%d ,%d > \n", "num",row,col );
			
		}

		

		return;
	}
	FILE_NOT_ENDED = false;
}

int main(){
	FILE *fa, *fb;
	char ca, cb;
	fa = fopen("HelloWorld.c", "r");
	if(fa == NULL){
		printf("Cannot open file \n");
		exit(0);
	}
	fb = fopen("q4out.c", "w");
	
	while(FILE_NOT_ENDED){
		getNextToken(fa,fb);
	}

	return 0;
}