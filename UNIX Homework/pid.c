#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(void) {
    printf("hello world! pid:%ld\n",(long)getpid());
    exit(0);
}
