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
    while((entry  = readdir(dp)) != NULL)
    {
        lstat(entry->d_name, &statbuf);
        if(strcmp(".",entry ->d_name) == 0 ||  strcmp("..",entry ->d_name) == 0) continue;

        printf("%*s%s/\t",depth,"",entry->d_name);
        printf("%*s",depth,"" );
        printf("\t%ld\t",statbuf.st_ino);
        printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
        printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
        printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
        printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
        printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
        printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
        printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
        printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
        printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
        printf("\n");

        //Code that checks for directory and the calls recursively
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
