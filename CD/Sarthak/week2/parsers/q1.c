#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int curr = 0;
char str[100];

void S();
void T();
void TPrime();


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
Sa | > | ( T )
TST'
T' -> ,ST' | epsi
*/

void S(){
	if(str[curr] == 'a' || str[curr] == '>'){
		curr++;
		return;
	}
	else if(str[curr] == '('){
		curr++;
		T();
		if(str[curr] == ')'){
			curr++;
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
	TPrime();
}

void TPrime(){
	if(str[curr] == ','){
		curr++;
		S();
		TPrime();
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