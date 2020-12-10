#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	int a=20;
	float f=100.0;
	char c='#';
	
    printf("%d\n",c);
	printf("%x\n",a);
	printf("%lf\n",f);
	printf("%c\n",c);
	printf("%e\n",f);
	return 0;
}