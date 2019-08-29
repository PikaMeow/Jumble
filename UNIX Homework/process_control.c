#define MAXLINE 4096
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int
main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf("%% ");
    while(fgets(buf,MAXLINE,stdin)!=NULL) {
        if(buf[strlen(buf)-1]=='\n') {
            buf[strlen(buf)-1]=0;
        }

    if((pid=fork())<0) {
         fprintf(stderr,"fork error.\n");
    } else if(pid==0) {
        execlp(buf,buf,(char*)0);
        fprintf(stderr,"Can't execute %s.Error:%s\n",buf,strerror(errno));
        exit(127);
    }
    if((pid=waitpid(pid,&status,0))<0) {
         fprintf(stderr,"waitpid error.\n");
    }
    printf("%% ");
    }
}
