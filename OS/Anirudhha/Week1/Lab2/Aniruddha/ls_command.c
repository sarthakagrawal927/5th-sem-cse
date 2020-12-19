#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
void printdir(char *dir, int depth)
{
	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;
	if((dp = opendir(dir)) == NULL) 
		{
			fprintf(stderr,"cannot open directory: %s\n", dir);
			return;
		}
	chdir(dir);
	while((entry = readdir(dp)) != NULL) 
		{
			lstat(entry->d_name,&statbuf);
			if(S_ISDIR(statbuf.st_mode)) 
			{
				/* Found a directory, but ignore . and .. */
				if(strcmp(".",entry->d_name) == 0 || strcmp("..",entry->d_name) == 0)
					continue;
			}
			else 
				{
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
					printf("%ld\t",statbuf.st_size);
					printf("Last modified time: %s", ctime(&statbuf.st_mtime));
					printf("\t%*s%s\n",depth,"",entry->d_name);
				}
		}
	chdir("..");
	closedir(dp);
}

int main()
{
	printf("Directory scan of Current Directory:\n");
	printdir(".",0);
	printf("done.\n");
	exit(0);
}
