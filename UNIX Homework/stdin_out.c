#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define BUFFSIZE 4096
int main(void) {
    int n;
    char buf[BUFFSIZE];
    while((n=read(STDIN_FILENO,buf,BUFFSIZE))>0) {
        if(write(STDOUT_FILENO,buf,n)!=n) {
            fprintf(stderr,"write error,Error:%s\n",strerror(errno));
        }
    }
    if(n<0) {
        fprintf(stderr,"read error,Error:%s\n",strerror(errno));
    }
    exit(0);
}
