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

	struct sockaddr_in server_addr, client_addr;
	int server_sockfd, server_addr_len, client_addr_len;

	char buffer[SZ];
	char *request = "SEND_TIME";
	int process_id = -1;

	server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;
	server_addr_len = sizeof(server_addr);
	client_addr_len = sizeof(client_addr);

	sendto(server_sockfd, request, SZ, 0, (struct sockaddr *)&server_addr, server_addr_len);
	recvfrom(server_sockfd, buffer, SZ, 0, (struct sockaddr *)&client_addr, &client_addr_len);
	printf("Time from server - %s", buffer);
	recvfrom(server_sockfd, &process_id, sizeof(int), 0, (struct sockaddr *)&client_addr, &client_addr_len);
	printf("Process id from server - %d\n", process_id);

	close(server_sockfd);

}