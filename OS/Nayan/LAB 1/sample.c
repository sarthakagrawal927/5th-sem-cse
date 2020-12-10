#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char const *argv[])
{   
    //write
	if((write(1,"Here is some data\n",18))!=18)
		write(2,"A write error has occured on file descriptor 1\n",46);
    
    //read
    char buf[128];
    int nread;
    nread=read(0,buf,128);
    if(nread==-1)
    	write(2,"A write error has occured\n",26);
    if((write(1,buf,nread))!=nread)
    	write(2,"A write error has occured on file descriptor 1\n",27);
	
	//copy file
	char c;
	int in,out;
	in = open("in.txt",O_RDONLY);
	out = open("out.txt",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
	while(read(in,&c,1)==1)
		write(out,&c,1);
    
	exit(0);
}