#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int main(int argc, char const *argv[])
{
	int i=10;
	float f=10.10;
	char c='a';
	char s[]="Hello World";
	float k = 12131.5234523452;
	errno=EPERM;

	printf("Integer: %d\n",i);
	printf("Float: %f\n",f);
	printf("Character: %c\n",c);
	printf("String: %s\n",s);
	printf("Errno string(EPERM): %m\n");
	printf("Pointer Address : %p\n",&i);
	printf("Scifi Notation %e\n",k);

	return 0;
}