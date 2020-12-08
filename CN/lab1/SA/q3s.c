#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server. 
int getResult(int a, int b, char c){
	if(c == '+') return a+b;
	if(c == '-') return a-b;
	if(c == '*') return a*b;
	if(c == '/') return a/b;
	if(c == '%') return a%b;
	return -9999;
}

// ASCII - 48 - 57
void servfunc(int sockfd)
{
	char buff[MAX];
	int n;
	int siz;
	// infinite loop for chat 

	for (;;)
	{
		bzero(buff, MAX);

		// read the message from client and copy it in buffer 
		read(sockfd, buff, sizeof(buff));

		// print buffer which contains the client contents 
		printf("[Server PORT %d]From client: %s\n To client : ",PORT, buff);

		int num1 =0, num2=0;
		int i = 0;

		//get first number
		while(buff[i] <= 57 && buff[i] >= 48)
		{
			num1 = num1 * 10 + (int)(buff[i++] - 48);
		}
		i++; //ignoring space

		//get second number
		while(buff[i] <= 57 && buff[i] >= 48)
		{
			num2 = num2 * 10 + (int)(buff[i++] - 48);
		}
		i++;
		int res = getResult(num1, num2, buff[i]);
		char resu[10];
		sprintf(resu,"%d",res);

		// bzero(buff, sizeof(buff));
		
		write(sockfd, resu, sizeof(resu));
		printf("Result is %d\n",res);

		if (strncmp("QUIT", buff, 4) == 0)
		{
			printf("Server Exit...\n");
			break;
		}
	}
}

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*) &servaddr, sizeof(servaddr))) != 0)
	{
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0)
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");

	len = sizeof(cli);

	// Accept the data packet from client and verification 
	connfd = accept(sockfd, (SA*) &cli, &len);
	if (connfd < 0)
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");

	// Function for chatting between client and server 
	servfunc(connfd);

	// After sending exit message close the socket 
	close(sockfd);
}