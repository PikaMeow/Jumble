/*
NAME tcpm—trivially copy a file via mmap/memcpy
SYNOPSIS
tcpm source target
DESCRIPTION
The tcpm utility copies the contents of the source to target. That is, behaves entirely the same as tcp(1).
Unlike tcp(1), tcpm uses mmap(2) and memcpy(2) instead of read(2) and write(2), which is why it can be rewarded with up to 10 extra credit points.
EXAMPLES
The following examples show common usage:
tcpm file1 file2
tcpm file1 dir
tcpm file1 dir/file2
tcpm file1 dir/subdir/subsubdir/file2
EXIT STATUS
tcpm exits 0 on success, and >0 if an error occurred.
SEE ALSO
tcp(1),lseek(2),mmap(2),memcpy(2)
NOTES
The code for the tcpm utility is, of course, well-formatted and can be compiled using the -Wall flags without any errors or warnings.
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
int
main(int argc,char *argv[]) {
    int from_fd,to_fd;
    int f_length;
    void *from_map;
    void *to_map;
    DIR *dp;
    if(argc!=3) {
         fprintf(stderr,"Usage : %s from file to file/dir.\n",argv[0]);
         exit(1);
    }
    if((from_fd=open(argv[1],O_RDONLY))==-1) {
         fprintf(stderr,"Open %s Error: %s.\n",argv[1],strerror(errno));
         exit(1);
    }
    if((to_fd=open(argv[2],O_RDWR|O_CREAT,S_IRUSR|S_IWUSR))==-1) {
        if((dp=opendir(argv[2]))!=NULL) {
             char tmp[100];
             strcpy(tmp,argv[2]);
             strcat(tmp,"/");
             strcat(tmp,argv[1]);
             if((to_fd=open(tmp,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR))==-1) {
                  fprintf(stderr,"Open %s Error: %s.\n",tmp,strerror(errno));
                  exit(1);
             }
             closedir(dp);
        } else {
             fprintf(stderr,"Open %s Error: %s.\n",argv[2],strerror(errno));
             exit(1);
        }
    }
    f_length=lseek(from_fd,0,SEEK_END);
    lseek(from_fd,0,SEEK_SET);
    ftruncate(to_fd,f_length);
    if((from_map=mmap(0,f_length,PROT_READ,MAP_SHARED,from_fd,0))==MAP_FAILED) {
        fprintf(stderr,"Map %s to memory fail. Error:%s\n",argv[1],strerror(errno));
        exit(1);
    }
    if((to_map=mmap(0,f_length,PROT_READ|PROT_WRITE,MAP_SHARED,to_fd,0))==MAP_FAILED) {
        fprintf(stderr,"Map to memory fail. Error:%s\n",strerror(errno));
        exit(1);
    }
    if(memcpy(to_map,from_map,f_length)==NULL) {
         fprintf(stderr,"Copy file failed. Error:%s\n",strerror(errno));
         munmap(from_map,f_length);
         munmap(to_map,f_length);
         exit(1);
    }
    close(from_fd);
    close(to_fd);
    munmap(from_map,f_length);
    munmap(to_map,f_length);
    exit(0);
}
