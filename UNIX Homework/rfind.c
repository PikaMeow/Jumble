#include <stdlib.h>
#include <fnmatch.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include "wildchar.h"
void findByName(DIR *dp,char *dir,char *pattern) {
    struct dirent *dirp;
    char *file_name;
    while((dirp=readdir(dp))!=NULL) {
        DIR *subdp;
        file_name=dirp->d_name;
        char subpath[sizeof(dir)+sizeof(file_name)+5]={'\0'};
        sprintf(subpath,"%s/%s",dir,file_name);
        if(strcmp(file_name,".")==0 || strcmp(file_name,"..")==0) continue;
        if(dirp->d_type==DT_DIR) {
            if((subdp=opendir(subpath))==NULL) {
                fprintf(stderr,"Can't open %s. Error:%s \n",file_name,strerror(errno));
                exit(1);
            }
            else {
                findByName(subdp,subpath,pattern);
            }
            continue;
        }
        if((WildCharMatch(file_name,pattern,0))==1) {
            printf("Find matched file:%s\n",subpath);
        }

    }
    closedir(dp);
}

void findByContent(DIR *dp,char *dir,char *pattern) {
    struct dirent *dirp;
    char *file_name;
    char buffer[1024];
    int read_bytes;
    while((dirp=readdir(dp))!=NULL) {
        DIR *subdp;
        int r_fd;
        file_name=dirp->d_name;
        char subpath[sizeof(dir)+sizeof(file_name)+5]={'\0'};
        sprintf(subpath,"%s/%s",dir,file_name);
        if(strcmp(file_name,".")==0 || strcmp(file_name,"..")==0) continue;
        if(dirp->d_type==DT_DIR) {
            if((subdp=opendir(file_name))==NULL) {
                fprintf(stderr,"Can't open %s. Error:%s \n",file_name,strerror(errno));
                exit(1);
            }
            else {
                findByContent(subdp,subpath,pattern);
            }
            continue;
        }
        if((r_fd=open(subpath,O_RDONLY))==-1) {
            fprintf(stderr,"Can't open file %s. Error:%s\n",file_name,strerror(errno));
        }
        while((read_bytes=read(r_fd,buffer,1024))) {

             if(read_bytes==-1 && errno != EINTR) break;
             if(WildCharMatch(buffer,pattern,0)==1) {
                printf("Find matched file:%s\n",subpath);
                break;
             }
             memset(buffer,0,sizeof(buffer));
        }
        close(r_fd);
    }
    closedir(dp);
}


void findByBoth(DIR *dp,char *dir,char *pattern1,char *pattern2) {
    struct dirent *dirp;
    char *file_name;
    while((dirp=readdir(dp))!=NULL) {
        DIR *subdp;
        int r_fd;
        int read_bytes;
        char buffer[1024];
        file_name=dirp->d_name;
        char subpath[sizeof(dir)+sizeof(file_name)+5]={'\0'};
        sprintf(subpath,"%s/%s",dir,file_name);
        if(strcmp(file_name,".")==0 || strcmp(file_name,"..")==0) continue;
        if(dirp->d_type==DT_DIR) {
            if((subdp=opendir(subpath))==NULL) {
                fprintf(stderr,"Can't open %s. Error:%s \n",file_name,strerror(errno));
                exit(1);
            }
            else {
                findByBoth(subdp,subpath,pattern1,pattern2);
            }
            continue;
        }
        if((WildCharMatch(file_name,pattern1,0))==1) {
            if((r_fd=open(subpath,O_RDONLY))==-1) {
                fprintf(stderr,"Can't open file %s. Error:%s\n",file_name,strerror(errno));
            }
            while((read_bytes=read(r_fd,buffer,1024))) {

                 if(read_bytes==-1 && errno != EINTR) break;
                 if(WildCharMatch(buffer,pattern2,0)==1) {
                     printf("Find matched file:%s\n",subpath);
                     break;
                 }
                 buffer[0]=0;
             }
             close(r_fd);
        }

    }
    closedir(dp);

}

int main(int argc,char **argv) {
    DIR *dp;
    if(argc!=4&&argc!=6) {
        fprintf(stderr,"Usage: %s find file(s) by name or content.\n",argv[0]);
        exit(1);
    }

    if(argc==4) {
        if(strcmp(argv[1],"-name")!=0 && strcmp(argv[1],"-content")!=0 ) {
            fprintf(stderr,"Please input option \'-name\' or \'-content\' \n");
            exit(1);
        }
        if((dp=opendir(argv[3]))==NULL) {
            fprintf(stderr,"Can't open %s. Error:%s\n",argv[3],strerror(errno));
        }
        if(strcmp(argv[1],"-name")==0) {
            findByName(dp,argv[3],argv[2]);
        }
        if(strcmp(argv[1],"-content")==0) {
            char tmp[sizeof(argv[2])+5]={'\0'};
            sprintf(tmp,"%s%s%s","*",argv[2],"*");
            findByContent(dp,argv[3],tmp);
        }
    }
    if(argc==6) {
        if((dp=opendir(argv[5]))==NULL) {
            fprintf(stderr,"Can't open %s. Error:%s\n",argv[3],strerror(errno));
        }
        if(strcmp(argv[1],"-name")==0) {
            char tmp[sizeof(argv[4])+5]={'\0'};
            sprintf(tmp,"%s%s%s","*",argv[4],"*");
            findByBoth(dp,argv[5],argv[2],tmp);
        } else if(strcmp(argv[1],"-content")==0) {
            char tmp[sizeof(argv[2])+5]={'\0'};
            sprintf(tmp,"%s%s%s","*",argv[2],"*");
            findByBoth(dp,argv[5],argv[4],tmp);
        } else {
            fprintf(stderr,"Please input option \'-name\' and \'-content\' \n");
        }
    }
}
