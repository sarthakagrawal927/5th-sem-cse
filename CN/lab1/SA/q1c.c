#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#define PORT 5000
#define MAXLINE 1000

int main()
{

    int buffer[100][100];
    int sockfd, n,len;
    struct sockaddr_in servaddr, cliaddr;

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = PORT;
    servaddr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	int row = 3,col = 3;
    // printf("Enter size\n");
    // scanf("%d %d",&row,&col);

    // sendto(sockfd, row, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    // sendto(sockfd, col, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    int arr[10];
    printf("Enter a matrix with %d rows and %d columns",row,col);
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            scanf("%d", &arr[j]);
        }
        sendto(sockfd, arr, MAXLINE, 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
    }

    len = sizeof(cliaddr);

    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            printf("%d", buffer[i][j]);
        }
    }

    close(sockfd);
    return 0;
}
