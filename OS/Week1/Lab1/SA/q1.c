#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#define SZ 1000

int main(int argc, char const *argv[])
{
	char c;
	if(argc < 3){
		printf("Insufficient Arguments\n");
		exit(0);
	}

	int in = open(argv[2],O_RDONLY);
	if(in == -1){
		printf("File Not found\n");
		exit(0);
	}

	printf("The word is %s\n",argv[1]);

	char buffer[SZ];
    int buffer_length;
    char line[SZ];

	read(in, buffer, sizeof(buffer));
    buffer_length=strlen(buffer);

    int idx=0;
    for (int i = 0; i < buffer_length; i++) 
    {
        if (buffer[i] == '\n') 
        {
            line[idx] = '\0';
            if (strstr(line, argv[1]) != NULL) 
            {
                printf("%s\n", line);
            }
            idx = 0;
        } 
        else 
        {
            line[idx++] = buffer[i];
        }
    }
	in = open(argv[2],O_RDONLY);
	return 0;
}