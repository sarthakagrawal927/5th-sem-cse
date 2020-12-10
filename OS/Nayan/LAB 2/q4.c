#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

void print_all(DIR* dp) {
    struct dirent* dentry;
    while(1) {
        dentry = readdir(dp);
        if (dentry == NULL) {
            break;
        }
        if (strcmp(dentry->d_name, ".") == 0 || strcmp(dentry->d_name, "..") == 0) {
            continue;
        }
        printf("%s\n", dentry->d_name);
    }
}

int main(int argc, char** argv) {

    DIR* dp1;
    dp1 = opendir("/usr/lib/rpm");
    print_all(dp1);
    return 0;
}