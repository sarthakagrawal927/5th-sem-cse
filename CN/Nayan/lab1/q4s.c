#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 3000
#define SZ 1000

int main() {

	struct sockaddr_in client_addr, server_addr;
	int server_sockfd, client_sockfd, server_addr_len, client_addr_len;

	char buffer[SZ];
	time_t rawtime;
	struct tm * timeinfo;
	int process_id = -1;

	server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;
	server_addr_len = sizeof(server_addr);
	bind(server_sockfd, (struct sockaddr *)&server_addr, server_addr_len);
	client_addr_len = sizeof(client_addr);

	recvfrom(server_sockfd, buffer, SZ, 0, (struct sockaddr *)&client_addr, &client_addr_len);
	time (&rawtime);
	timeinfo = localtime (&rawtime);
	strcpy(buffer, asctime (timeinfo));
	sendto(server_sockfd, buffer, SZ, 0, (struct sockaddr *)&client_addr, client_addr_len);
	process_id = getpid();
	sendto(server_sockfd, &process_id, sizeof(int), 0, (struct sockaddr *)&client_addr, client_addr_len);

	close(client_sockfd);

}