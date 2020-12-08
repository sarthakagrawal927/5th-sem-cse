#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#define PORT 5000
#define MAXLINE 1000

int main()
{
    int buffer[100];
    int result[100][100];
    int servsockfd, len,n;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    servsockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    bind(servsockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    len = sizeof(cliaddr);

    int row = 3,col = 3;
    // n = recvfrom(servsockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&cliaddr, &len);
    // row = buffer[0];
    // col = buffer[1];

    // printf("Recieved %d %d ada\n",row,col );

    for(int i=0;i<row;i++)
    {
        n = recvfrom(servsockfd, buffer, sizeof(buffer),0, (struct sockaddr*)&cliaddr, &len);
        for(int j=0;j<col;j++)
        {
            result[i][j] = buffer[j];
        }
    }

    printf("Printing 2d-array\n");

    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    getchar();
    close(servsockfd);
    return 0;
}