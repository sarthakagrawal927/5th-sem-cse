#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <strings.h>

#define PORT 3000
#define MAXLINE 1000

int main(int argc, char const *argv[])
{
    char buffer[100];
    char *message = "FUck u";
    int sockfd, n ,len;
    struct sockaddr_in cliaddr, servaddr;

    bzero(&servaddr, sizeof(servaddr));

    //socket configured
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = PORT;
    servaddr.sin_family = AF_INET;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sendto(sockfd , message, MAXLINE, 0, (struct sockaddr*)&servaddr , sizeof(servaddr));
    len = sizeof(cliaddr);

    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);

    buffer[n] = '\0';
    printf("message from server is %s",buffer);
    getchar();

    close(sockfd);

    return 0;
}
