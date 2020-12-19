#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void S();
void U();
void V();
void W();

void invalid()
{
	printf("-----------------ERROR!----------------\n");
	exit(0);
}

void valid()
{
	printf("----------------SUCCESS!---------------\n");
	exit(0);
}

/*
SUVW
U (S) | aSb | d
V  aV | ε
W  cW | ε
*/

void S(){
	U();
	V();
	W();
}

void U(){
	if(str[curr] == '('){
		curr++;
		S();
		if(str[curr] == ')'){
			curr++;
			return;
		}
		else invalid();
	}
	else if(str[curr] == 'd') {
		curr++;
		return;
	}
	else if(str[curr] == 'a'){
		curr++;
		S();
		if(str[curr] == 'b'){
			curr++;
			return;
		}
		else invalid();
	}
	else invalid();
}

void V(){
	if(str[curr] == 'a'){
		curr++;
		V();
	}
	return;
}

void W(){
	if(str[curr] == 'c'){
		curr++;
		W();
	}
	return;
}


int main(){
	printf("EnterString : \n");
	scanf("%s",str);
	S();
	if(str[curr] == '$') valid();
	else invalid();
	return 0;
}