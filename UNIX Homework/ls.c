#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
int
main(int argc,char **argv) {
    DIR* dp;
    struct dirent *dirp;
    if(argc!=2) {
        fprintf(stderr,"Usage: ls directory_name");
    }
    if((dp=opendir(argv[1]))==NULL) {
        fprintf(stderr,"Can't open %s. Error:%s",argv[1],strerror(errno));
    }
    while((dirp=readdir(dp))!=NULL) {
         printf("%s\n",dirp->d_name);
    }
    closedir(dp);
    exit(0);
}
