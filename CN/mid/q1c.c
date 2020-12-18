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

#define PORT 5555

int main()
{
    int sd,len,n;
    struct sockaddr_in seraddr;
    //create socket
    sd=socket(AF_LOCAL,SOCK_STREAM,0);
    //name 
    seraddr.sin_family=AF_LOCAL;
    seraddr.sin_port=htons(PORT);
    seraddr.sin_addr.s_addr=inet_addr("172.16.57.152");
    
    len=sizeof(seraddr);
    //connect to server
    int result=connect(sd,(struct sockaddr*)&seraddr,len);
        char buf[100];
        printf("client starting\n");
        printf("Enter the character : \n");
        scanf("%c",buf);
        //write to server or read from server
        write(sd,buf,sizeof(buf));
        read(sd,buf,sizeof(buf));
        printf("Server responded with message : %s \n",buf);
        printf("closing client\n");
        
        //close socket
        close(sd);
        
        return 0;

}