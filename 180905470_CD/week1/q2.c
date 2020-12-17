# include <stdio.h>

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

int main(int argc, char const *argv[])
{
	FILE *fa,*fb; int ca,cb;
	removeComments();

	fa = fopen("q1out.c","r");
	if(fa == NULL){
		printf("Cannot open\n");
		return 0;
	}
	fb = fopen("q2tempout.c","w");
	ca = getc(fa);
	while(ca != EOF){
		if( ca == '#'){
			do{
				ca = getc(fa);
			}while(ca != '\n');
		}
		putc(ca,fb);
		ca = getc(fa);
	}
	
	fclose(fa);
	fclose(fb);

	fa= fopen("q2tempout.c","r");
		if(fa == NULL){
		printf("Cannot open\n");
		return 0;
	}
	fb = fopen("q2out.c","w");
	ca = getc(fa);
	while(ca == '\n'){
			ca = getc(fa);
		}
	while(ca != EOF){
		
		putc(ca,fb);
		ca = getc(fa);
	}
	
	fclose(fa);
	fclose(fb);

	if (remove("q2tempout.c") == 0) printf("Deleted successfully"); 
	return 0;
}