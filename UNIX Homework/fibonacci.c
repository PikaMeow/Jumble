#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    int a=atoi(argv[1]);
    if(a<=0||argc==1) {
        fprintf(stderr,"Please output at least one number.\n");
    }
    int fib0=0;
    int fib1=1;
    pid_t pid;
    pid=fork();
    if(pid==0) {
        if(a>=1) {
             printf("%d ",fib0);
        if(a>=2) {
             printf("%d ",fib1);
            for(int i=1;i<=a-2;i++) {
                int fib2=fib1+fib0;
                printf("%d ",fib2);
                fib0=fib1;
                fib1=fib2;
            }
        }
        printf("\n");
        }
    }
    else if(pid>0) {
         wait(NULL);
         exit(0);
    }
}
