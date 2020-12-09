#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 3000
#define SZ 1000

int main() {

	struct sockaddr_in server_addr;
	int server_sockfd, server_addr_len;

	char buffer[SZ];

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;
	server_addr_len = sizeof(server_addr);
	connect(server_sockfd, (struct sockaddr *)&server_addr, server_addr_len);

	printf("Enter operand1: ");
	scanf("%s", buffer);
	write(server_sockfd, buffer, SZ);
	printf("Enter operand2: ");
	scanf("%s", buffer);
	write(server_sockfd, buffer, SZ);
	printf("Enter operator: ");
	scanf("%s", buffer);
	write(server_sockfd, buffer, SZ);
	read(server_sockfd, buffer, SZ);
	printf("Result by server -> %s\n", buffer);

}