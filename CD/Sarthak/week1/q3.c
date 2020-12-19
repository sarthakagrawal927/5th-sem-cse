#include <stdio.h> 
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
void removeComments(){
	FILE *fa,*fb; int ca,cb;

	fa = fopen("q1in.c","r");
	if(fa == NULL){
		printf("Cannot open\n");
			return;
	}
	fb = fopen("q1out.c","w");
	ca = getc(fa);
	while(ca != EOF){
		if( ca == ' '){
			putc(ca,fb);
			while(ca == ' ') ca = getc(fa);
		}
		if(ca == '/'){
			cb = getc(fa);
			if(cb == '/'){
				while(ca != '\n') ca = getc(fa);
				putc(ca,fb);
			}
			else if( cb == '*'){
				do{
					while(ca != '*') ca = getc(fa);
					ca = getc(fa);
				}while(ca != '/');
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

char key[32][10] = {
	"auto","double","int","struct","break","else","long",
      "switch","case","enum","register","typedef","char",
      "extern","return","union","const","float","short",
      "unsigned","continue","for","signed","void","default",
      "goto","sizeof","voltile","do","if","static","while"
};

int existsInKey(char* word){
	// printf("%s\n",word );
	for(int i = 0; i < 32; i++){
		if(strcmp(key[i], word) == 0) return 1;
	}
	return 0;
}

char* toUpper(char* word){
	  for(int i=0;i<=strlen(word);i++){
      if(word[i]>=97&&word[i]<=122)
         word[i]=word[i]-32;
   }
  return word;
}

int main(int argc, char const *argv[])
{
	removeComments();
	FILE *fa; int ca,cb;

	fa = fopen("q1out.c","r");
	if(fa == NULL){
		printf("Cannot open\n");
		return 0;
	}
	ca = getc(fa);
	char word[20] ; int i = 0;

	while(ca != EOF){
		if(isalpha(ca) != 0) word[i++] = ca;
		else if(word[0] != 0){
			if(existsInKey(word)) printf("%s\n",toUpper(word));
			i = 0;
			for(size_t i = 0; i < sizeof word; ++i)
  				word[i] = 0;
		}
		ca = getc(fa);
	}
	fclose(fa);
	return 0;
}