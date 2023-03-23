#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <ftw.h>

long long full_size=0;
int fn(const char *path,const struct stat *stats,int typeflag){
    if(S_ISDIR(stats->st_mode) == 0){
        printf("%s %ld\n",path,stats->st_size);
        full_size += stats->st_size;
    }
    return 0;
}


int main(int argc,char **argv){

    if (argc != 2){
        printf("wrong number of arguments");
        return 1;
    }

    char * current_directory = argv[1];
    if (ftw(current_directory,fn,1) == -1){
        printf("ftw doesn't work");
        return 1;
    }
    printf("Summary size of files: %lld\n",full_size);
    return 0;
}