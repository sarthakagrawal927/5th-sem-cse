#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define PORT 5000
#define MAXLINE 1000

int main() {
	char buffer[100];
	int sockfd,n,len;
	struct sockaddr_in servaddr,cliaddr;

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	servaddr.sin_family = AF_INET;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);
	while(1){
		printf("Enter row for matrix\n");
		scanf("%[^\n]%*c",buffer);
		if(strcmp(buffer,"stop")==0) {
			printf("\n stopping the client");
			sendto(sockfd,buffer,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
			close(sockfd);
			break;
		}
		else {
			sendto(sockfd,buffer,MAXLINE,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		}
	}
	return 0;
}