#include<stdio.h>
#include <errno.h>
int main()
{
	int i=10;
	float f=10.10;
	char c='a';
	char s[]="Hello World";
	errno=EPERM;
	printf("Integer: %d\n",i);
	printf("Float: %f\n",f);
	printf("Character: %c\n",c);
	printf("String: %s\n",s);
	printf("Errno string(EPERM): %m\n");
	return 0;
}
