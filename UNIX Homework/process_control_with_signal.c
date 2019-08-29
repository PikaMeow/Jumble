#define MAXLINE 4096
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
static void sig_int(int);
void
sig_int(int signo) {
    printf("interrupt.\n%% ");
}
int
main(void) {
    char buf[MAXLINE];
    pid_t pid;
    int status;
    printf("%% ");

    if(signal(SIGINT,sig_int)==SIG_ERR) {
         fprintf(stderr,"signal error.");
    }
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
