#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc,char ** argv){

    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
        return 1;
    }

    DIR * current_directory = opendir(cwd);
    if (current_directory == NULL){
        perror("directory did not open");
        return 1;
    }

    struct dirent* file;
    struct stat file_stat;
    long long sum_size = 0;
    file = readdir(current_directory);
    while (file != NULL){
        stat(file->d_name,&file_stat);
        if (S_ISDIR(file_stat.st_mode)==0){
            printf("%s %ld\n",file->d_name,file_stat.st_size );
            sum_size += file_stat.st_size;
        }
        file = readdir(current_directory);

    }
    printf("summary size of all files: %lld\n",sum_size);

    return 0;

}