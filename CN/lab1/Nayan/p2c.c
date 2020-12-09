#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 150
#define PORT 5000
#define MAXLINE 1000

void main()
{
    int sockfd,retval;
    int recedbytes,sentbytes, recans;
    struct sockaddr_in serveraddr;
    char buff[MAXSIZE], ans[MAXSIZE], test[MAXSIZE];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("\nSocket Creation Error");

    }
    printf("\nSocket ID : %d\n",sockfd);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(PORT);
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    retval=connect(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    if(retval==-1)
    {
        printf("Connection error");
    }
    while(1){
        printf("Enter the text : ");
        scanf("%s",buff);
        sentbytes=send(sockfd,buff,sizeof(buff),0);
        recedbytes=recv(sockfd,ans,sizeof(ans),0);
        if(strcmp(ans,"QUIT") == 0)
        {
            puts("Stopping");
            sentbytes=send(sockfd,ans,sizeof(ans),0);
            close(sockfd);
            break;
        }

        printf("String converted to uppercase: %s \n",ans);

    }
}
