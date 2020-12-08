#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define PORT 5000
#define MAXLINE 1000

char mat[100][100];
int row=0;

void print_matrix() {
	int i;
	for(i=0;i<row;i++)
		printf("%s\n",mat[i]);
}

int main() {
	char buffer[100];
	
	int c=0;
	int servsockfd,len,n;
	struct sockaddr_in servaddr,cliaddr;
	bzero(&servaddr,sizeof(servaddr));

	servsockfd = socket(AF_INET,SOCK_DGRAM,0);

	if(servsockfd == -1) {
		printf("\nSocket error");
	} else {
		printf("\n Socket created \n");
	}

	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;
	bind(servsockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));

	len = sizeof(cliaddr);

	while(1){
		n = recvfrom(servsockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
		//buffer[n]='\0';
		if(strcmp(buffer,"stop")==0) {
			printf("Matrix is \n");
			print_matrix();
			printf("\nstopping server\n");
			close(servsockfd);
			break;
		}
		else {
			strcpy(mat[row++],buffer); 
			printf("Matrix is : \n");
			print_matrix();
			printf("\n");
		}	
	}
	return 0;
}