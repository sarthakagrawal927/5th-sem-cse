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

int main(int argc, char const *argv[])
{
    struct sockaddr_in servaddr,cliaddr;
    int sd , len ,connfd;
    sd = socket(AF_INET, SOCK_STREAM,0);

    servaddr.sin_family= AF_INET;
    servaddr.sin_addr.s_addr= INADDR_ANY;
    servaddr.sin_port = PORT;

    connect(sd , (SA*) &servaddr, sizeof(servaddr));

    char buff[MAX];
            printf("client starting\n");
        printf("Enter the character : \n");
        scanf("%c",buff);
    write(sd, "hello",MAX);
    read(sd, buff,MAX);


    close(sd);
    return 0;
}
