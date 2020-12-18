#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include <strings.h>

#define PORT 3000
#define MAXLINE 1000

int main(){
    char buffer[100];
    int servsockfd, len, n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));    //files in 0 in servaddr

    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = PORT;
    servaddr.sin_family = AF_INET; // AF_LOCAL
    servsockfd = socket(AF_INET, SOCK_DGRAM,0);

    bind(servsockfd, (struct sockaddr*) &servaddr , sizeof(servaddr));

    len = sizeof(cliaddr);
    n = recvfrom(servsockfd, buffer , sizeof(buffer) , 0  ,(struct sockaddr*) &cliaddr,&len);
    buffer[n] = '\0';
    puts(buffer);
    
    sendto(servsockfd , buffer,n,0,  (struct sockaddr*) &cliaddr, sizeof(cliaddr));
    getchar();

    close(servsockfd);
}