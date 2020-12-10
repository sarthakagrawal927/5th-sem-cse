#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SZ 20
char buf[SZ];
int cur=0;

//grammar
//S->UVW
//U->(S) | aSb | d
//V-> aV | ε
//W->cW | ε

void U();
void V();
void W();

void valid(){
	printf("Success\n");
	exit(0);
}

void invalid(){
	printf("Error\n");
	exit(0);
}

void S(){
	U();
	V();
	W();
}

void U(){
	if(buf[cur]=='('){
		cur++;
		S();
		if(buf[cur]==')'){
			cur++;
			return;
		}
		else{
			invalid();
		}
	}
	else if(buf[cur]=='a'){
		cur++;
		S();
		if(buf[cur]=='b'){
			cur++;
			return;
		}
		else
			invalid();
	}
	else if(buf[cur]=='d'){
		cur++;
		return;
	}
	else
		invalid();
}

void V(){
	if(buf[cur]=='a'){
		cur++;
		V();
	}
}

void W(){
	if(buf[cur]=='c'){
		cur++;
		W();
	}
}

int main(){
	printf("Enter the string\n");
	scanf("%s", buf);
	S();
	if(buf[cur]=='$'){
		valid();
	}
	else
		invalid();
	return 0;
}