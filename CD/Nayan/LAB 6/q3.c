#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SZ 20
char buf[SZ];
int cur=0;

//grammar
//S->aAcBe
//A->Ab|b
//B->d

//prototype
void S();
void A();
void Aprime();
void B();

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
		A();
		if(buf[cur]=='c'){
			cur++;
			B();
			if(buf[cur]=='e'){
				cur++;
				return;
			}
			else
				invalid();
		}
		else
			invalid();
	}
}

void A(){
	if(buf[cur]=='b'){
		cur++;
		Aprime();
	}
}

void Aprime(){
	if(buf[cur]=='b'){
		cur++;
		Aprime();
	}
}

void B(){
	if(buf[cur]=='d'){
		cur++;
		return;
	}
}
int main(){
	printf("Enter the string\n");
	scanf("%s",buf);
	S();
	if(buf[cur]=='$')
		valid();
	else
		invalid();
	return 0;
}