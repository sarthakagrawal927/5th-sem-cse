#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SZ 20
char buf[SZ];
int cur = 0;

//grammar
//S -> (L) | a
//L -> L,S | S

void S();
void L();
void Lprime();

void valid()
{
	printf("Success\n");
	exit(0);
}

void invalid()
{
	printf("Error\n");
	exit(0);
}

void S()
{
	if (buf[cur] == '(')
	{
		cur++;
		L();
		if (buf[cur] == ')')
		{
			cur++;
			return;
		}
		else
			invalid();
	}
	else if (buf[cur] == 'a')
	{
		cur++;
		return;
	}
	else
		invalid();
}

void L()
{
	S();
	Lprime();
}

void Lprime()
{
	if (buf[cur] == ',')
	{
		cur++;
		S();
		Lprime();
	}
}

int main()
{
	printf("Enter the string\n");
	scanf("%s", buf);
	S();
	if (buf[cur] == '$')
	{
		valid();
	}
	else
		invalid();
	return 0;
}