#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
void printdir(char *dir, int depth)
{
	DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if((dp = opendir(dir)) == NULL){
        fprintf(stderr, "Cannot Open Directory%s\n", dir);
        return;
    }
    chdir(dir);
    while((entry = readdir(dp)) != NULL){
        lstat(entry -> d_name, &statbuf);
    
        if(S_ISDIR(statbuf.st_mode)){
            if(strcmp(".", entry -> d_name) ==0 || strcmp("..",entry -> d_name) ==0) continue;
            printf("%s \t\t", entry-> d_name );
            printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
            printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
            printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
            printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
            printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
            printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
            printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
            printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
            printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
            printf("\t%d\t",statbuf.st_uid);
            printf("\t%s", ctime(&statbuf.st_mtime));
            // printdir(entry -> d_name, depth+4);
            printf("Would you like to remove this directory ?\n" );
            char c;
            scanf("%c",&c);
            getchar();
            if(c == 'Y'){
            	int l = remove(entry->d_name);
            	if(l== 0){
            		printf("Success\n");
            	}
            }
        }
    }
    chdir("..");
    closedir(dp);
	return;
}

int main(int argc, char const *argv[])
{
    printdir(".",0);
    return 0;
}