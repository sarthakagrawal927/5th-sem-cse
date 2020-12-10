#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>



char temp[100];

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

void eraseComment(){
	FILE *fa, *fb;
	char ca, cb;
	fa = fopen("HelloWorld.c", "r");
	if(fa == NULL){
		printf("Cannot open file \n");
		exit(0);
	}
	fb = fopen("q1out.c", "w");
	ca = getc(fa);
	while (ca != EOF){
		if(ca==' '){
			putc(ca,fb);
			while(ca==' ')
				ca = getc(fa);
		}
		if (ca=='/'){
			cb = getc(fa);
			if (cb == '/'){
				while(ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*'){
				do{
					while(ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				}while (ca != '/');
			}
			else{
				putc(ca,fb);
				putc(cb,fb);
			}
		}
		else putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
}

int main(){
	eraseComment();




	FILE *fa, *fb;
	char ca, cb;
	fa = fopen("q1out.c", "r");
	if(fa == NULL){
		printf("Cannot open file \n");
		exit(0);
	}
	fb = fopen("q2out.c", "w");
	ca = getc(fa);
	while (ca != EOF){
		if(ca=='#'){
			// putc(ca,fb);
			int x=0;
			while(ca!='\n'){

				// ca = getc(fa);
				temp[x++] = ca;
				temp[x] = '\0';
				ca = getc(fa);
			}
			printf(" bool = %d \n",is_include() );
			if(!is_include() && !is_define() ){
				for(int k=0;k<x;++k){
					putc(temp[k],fb);
				}
			}

		}
	
		else putc(ca,fb);
		ca = getc(fa);
	}
	fclose(fa);
	fclose(fb);
	
	return 0;
}

