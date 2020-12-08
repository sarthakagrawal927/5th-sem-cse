#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAXSIZE 150
#define PORT 5000
#define MAXLINE 1000

int flag = 0;

char* strUpper(char* str){
    int i;
    for(i=0;i<strlen(str);i++){
        str[i]=toupper(str[i]);
    }

    return str;
}

int main()
{
    int sockfd,newsockfd,retval,n, actuallen;
    int recedbytes,sentbytes, sentans;
    struct sockaddr_in serveraddr,clientaddr;

    char buff[MAXSIZE], ans[MAXSIZE];
    char* temp_buf;
    int a=0;
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd==-1)
    {
        printf("\nSocket creation error");
    }

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(PORT);
    serveraddr.sin_addr.s_addr=htons(INADDR_ANY);
    bind(sockfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    puts("Server Running");

    listen(sockfd,1);

    actuallen=sizeof(clientaddr);
    newsockfd=accept(sockfd,(struct sockaddr*)&clientaddr,&actuallen);

    while(1){
        n=recv(newsockfd,buff,sizeof(buff),0);
        buff[n]='\0';
        if(strcmp(buff,"QUIT") == 0)
        {
            puts("Stopping");
            close(sockfd);
            close(newsockfd);
            break;
        }
        else
        {
            printf("The string sent by client is %s\n",buff);
            printf("Port: %d\n",ntohs(clientaddr.sin_port));
            printf("IP: %s\n",inet_ntoa(clientaddr.sin_addr));
            temp_buf = strUpper(buff);
            sentbytes = send(newsockfd,temp_buf,sizeof(temp_buf),0);
       }
   }
    return 0;
}
