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
  		//check if directory or not
  		if(S_ISDIR(statbuf.st_mode)){
  			//found a directory but ignore . and ..
  		    if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
  		    	continue;
  		    printf("%*s%s/\n",depth,"",entry->d_name);
  		    //recurse at a new indent level
  		    printdir(entry->d_name,depth+4);
  		}
  		else printf("%*s%s/\n",depth,"",entry->d_name);
  	}
  	chdir("..");
  	closedir(dp);
}

int main(int argc, char *argv[])
{
	printdir(argv[1],0);
	printf("done\n");
	return 0;
}