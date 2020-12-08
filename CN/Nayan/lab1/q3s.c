#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

#define PORT 3000
#define SZ 1000

int main() {

	struct sockaddr_in server_addr, client_addr;
	int server_sockfd, client_sockfd, server_addr_len, client_addr_len;

	char buffer[SZ];
	char operator;
	int operand1, operand2, result;

	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;
	server_addr_len = sizeof(server_addr);
	bind(server_sockfd, (struct sockaddr *)&server_addr, server_addr_len);
	listen(server_sockfd, 10);
	client_addr_len = sizeof(client_addr);

	while (1) {
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
		if (fork() == 0) {
			read(client_sockfd, buffer, SZ);
			sscanf(buffer, "%d", &operand1);
			read(client_sockfd, buffer, SZ);
			sscanf(buffer, "%d", &operand2);
			read(client_sockfd, buffer, SZ);
			sscanf(buffer, "%c", &operator);
			printf("%d %c %d = ", operand1, operator, operand2);
			switch (operator) {
				case '+':
					result = operand1 + operand2;
					break;
				case '-':
					result = operand1 - operand2;
					break;
				case '*':
					result = operand1 * operand2;
					break;
				case '/':
					result = operand1 / operand2;
					break;
			}
			printf("%d\n", result);
			sprintf(buffer, "%d", result);
			write(client_sockfd, buffer, SZ);
		}
		close(client_sockfd);
	}

}