#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

void printdir(char *dir, int depth){
    DIR *dp;
    struct dirent * entry;
    struct stat statbuf;
    if((dp = opendir(dir) )== NULL){
        printf("s");
        return ;
    }
    chdir(dir);
    while((entry  = readdir(dp)) != NULL){
        lstat(entry->d_name, &statbuf);
        if(strcmp(".",entry ->d_name) == 0 ||  strcmp("..",entry ->d_name) == 0) continue;
        printf("%*s%s/\n",depth,"",entry->d_name);
        if(S_ISDIR(statbuf.st_mode)){
            printdir(entry -> d_name, depth+4);
        }
  }
    chdir("..");
    closedir(dp);
}

int main(int argc, char const *argv[])
{
    printdir(".",0);
    return 0;
}
