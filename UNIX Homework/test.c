#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
int main(int argc,char *argv[]) {
    DIR *dp;
    printf("%d\n",argc);
    for(int i=0;i<argc;i++) {
        printf("%s ",argv[i]);
    }
    printf("\n");
    int r_fd=open("tcp.c",O_RDWR);
    int read_bytes;
    char buf[1024];
    while((read_bytes=read(r_fd,buf,1024))) {
         printf("%s\n",buf);
         memset(buf,0,sizeof(buf));
    }
    return 0;
}
