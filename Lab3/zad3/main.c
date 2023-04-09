#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


char exe_path[PATH_MAX];
int main(int argc, char ** argv){
//    printf("%d", argc);
    if (argc != 3){
        perror("wrong number of arguments");
        return 1;
    }

    DIR *directory;
    char *dir_path;
    dir_path = calloc(strlen(argv[1]),sizeof(char));
    strcpy(dir_path,argv[1]);

    struct dirent *entry_directory;


    if((directory = opendir(dir_path)) == NULL){
        perror("Path does not exist");
        return 1;
    }
    char *dest_path;
    realpath(argv[0],exe_path);

    while((entry_directory = readdir(directory)) != NULL){

        if (!strcmp(entry_directory->d_name, ".") || !strcmp(entry_directory->d_name, "..")){
            continue;
        }

        dest_path = calloc(PATH_MAX, sizeof(char));
        strcpy(dest_path,dir_path);
        strcat(dest_path,"/");
        strcat(dest_path,entry_directory->d_name);

        if (entry_directory->d_type == DT_DIR){
            if (fork() == 0){
                execl(exe_path,"main",dest_path,argv[2],NULL);
            }
        }else{
            FILE *file = fopen(dest_path,"r");
            char *buffer = calloc(strlen(argv[2]), sizeof(char));
            fread(buffer, sizeof(char), strlen(argv[2]),file);
            if (strcmp(buffer,argv[2]) == 0){
                printf("%s %d\n", dest_path, (int)getpid());
                fflush(NULL);
            }
            fclose(file);
        }
        free(dest_path);
    }
    while (wait(NULL) > 0);

    return 0;
}