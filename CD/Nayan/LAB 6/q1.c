#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SZ 20
char buf[SZ];
int cur=0;

//grammar
// S->a | > | ( T )
// T->T,S|S

//prototype
void S();
void T();
void Tprime();

void valid(){
	printf("Success\n");
	exit(0);
}
void invalid(){
	printf("Error\n");
	exit(0);
}

void S(){

	if(buf[cur]=='a'){
		cur++;
	}
	else if(buf[cur]=='>'){
		cur++;
	}
	else if(buf[cur]=='('){
		cur++;
		T();
		if(buf[cur]==')'){
			cur++;
			return;
		}
		else
			invalid();
	}
	else
		invalid();
}

void T(){
	S();
	Tprime();
}

void Tprime(){
	if(buf[cur]==','){
		cur++;
		S();
		Tprime();
	}
}

int main(){
	printf("Enter the string \n");
	scanf("%s", buf);
	S();
	if(buf[cur]=='$'){
		valid();
	}
	else
		invalid();
	return 0;
}