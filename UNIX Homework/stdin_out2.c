#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
int
main(void) {
    int c;
    while((c=getc(stdin))!=EOF) {
        if(putc(c,stdout)==EOF) {
           fprintf(stderr,"output error. Error:%s\n",strerror(errno));
        }
    }
    if(ferror(stdin)) {
        fprintf(stderr,"input error. Error:%s\n",strerror(errno));
    }
    exit(0);
}
