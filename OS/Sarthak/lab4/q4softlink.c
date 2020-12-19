#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	struct stat sb;
	int ret;
	if (argc < 2)
	{
		fprintf(stderr, "file name not mentioned%s\n",argv[0] );
		return 1;
	}

	ret = stat("./q4.c",&sb);
	if(ret){
		perror("stat");
		return 1;
	}

	printf("Number of Hard Links : %ld\n", sb.st_nlink);
	printf("Path right now\n /home/Desktop/180905470/OS/lab4/q3.c\n");

	int ret2 = symlink("./q4.c", argv[1]);

	if(ret2) perror("link");
	else printf("Linking Succes\n");

	int ret3 = stat("./q4.c",&sb);
	printf("No. of Hard Links : %ld\n",sb.st_nlink );

	int unl = unlink("./q4.c");
	if(unl == 0) printf("Unlinking Successs\n");

	int ret4 = stat(argv[1],&sb);
	printf("Path right now\n /home/Desktop/180905470/OS/lab4/%s\n",argv[1]);

	printf("Number of Hard Links : %ld\n", sb.st_nlink);

	return 0;
}