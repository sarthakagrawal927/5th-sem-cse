# include <stdio.h> 
int main(int argc, char const *argv[])
{
	FILE *fa,*fb; int ca,cb;

	fa = fopen("q1in.c","r");
	if(fa == NULL){
		printf("Cannot open\n");
		return 0;
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
	return 0;
}