#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void printdir(char *dir,int depth){
  	DIR *dp;
  	struct dirent *entry;
  	struct stat statbuf;
  	if((dp=opendir(dir))==NULL){
  		fprintf(stderr,"cannot open directory: %s\n",dir);
  		return;
  	}
  	chdir(dir);
  	while((entry=readdir(dp))!=NULL){
  		lstat(entry->d_name,&statbuf);
  	    if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
  		    continue;
  		if(S_ISDIR(statbuf.st_mode))printf("dir - ");
  		if(statbuf.st_mode & S_IRUSR)printf("r");else printf("-");
  		if(statbuf.st_mode & S_IWUSR)printf("w");else printf("-");
  		if(statbuf.st_mode & S_IXUSR)printf("x");else printf("-");
  		if(statbuf.st_mode & S_IRGRP)printf("r");else printf("-");
  		if(statbuf.st_mode & S_IWGRP)printf("w");else printf("-");
  		if(statbuf.st_mode & S_IXGRP)printf("x");else printf("-");
  		if(statbuf.st_mode & S_IROTH)printf("r");else printf("-");
  		if(statbuf.st_mode & S_IWOTH)printf("w");else printf("-");
  		if(statbuf.st_mode & S_IXOTH)printf("x");else printf("-");
  		printf(" %s\n",entry->d_name);
  			
  	}
  	closedir(dp);
}

int main(int argc, char *argv[])
{
	printdir(argv[1],0);
	printf("done\n");
	return 0;
}