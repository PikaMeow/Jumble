/*
NAME tcp —trivially copy a file
SYNOPSIS tcp source target
DESCRIPTION
The tcp utility copies the contents of the source to target.
If target is a directory, tcp will copy source into this directory.
EXAMPLES
The following examples show common usage:
tcp file1 file2
tcp file1 dir
tcp file1 dir/file2
tcp file1 dir/subdir/subsubdir/file2
EXIT STATUS
tcp exits 0 on success, and >0 if an error occurred.
SEE ALSO
tcpm(1), lseek(2), read(2), write(2)
NOTES
The code for the tcp utility is, of course, well-formatted and can be compiled using the -Wall flags without any errors or warnings.
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#define BUFFER_SIZE 1024
int
main (int argc,char *argv[]) {
    int from_fd,to_fd;
    int read_bytes,write_bytes;
    char buffer[BUFFER_SIZE];
    char *ptr;
    DIR *dp;
    if(argc!=3) {
        fprintf(stderr,"Usage: %s copy from file to file/dir.\n",argv[0]);
        exit(1);
    }
    if((from_fd=open(argv[1],O_RDONLY))==-1) {
        fprintf(stderr,"Open %s Error:%s\n",argv[1],strerror(errno));
        exit(1);
    }
    if((to_fd=open(argv[2],O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1) {
        if((dp=opendir(argv[2]))!=NULL) {
             char tmp[100];
             strcpy(tmp,argv[2]);
             strcat(tmp,"/");
             strcat(tmp,argv[1]);
             if((to_fd=open(tmp,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR))==-1) {
                fprintf(stderr,"Open %s Error:%s\n",tmp,strerror(errno));
                exit(1);
             }
             closedir(dp);
        } else {
        fprintf(stderr,"Open %s Error:%s\n",argv[2],strerror(errno));
        exit(1);
        }
    }
    while((read_bytes=read(from_fd,buffer,BUFFER_SIZE))) {
         if(read_bytes==-1 && errno != EINTR) break;
         else if(read_bytes > 0) {
             ptr=buffer;
             while((write_bytes=write(to_fd,ptr,read_bytes))) {
                 if(write_bytes==-1 && errno != EINTR ) break;
                 else if(write_bytes==read_bytes) {
                     break;
                 }
                 else if(write_bytes>0) {
                      ptr+=write_bytes;
                      read_bytes-=write_bytes;
                 }
             }
             if(write_bytes == -1 ) break;
         }
    }
    close(from_fd);
    close(to_fd);
    exit(0);
}
