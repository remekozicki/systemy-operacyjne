#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <time.h>
#define BUFF_SIZE 1024


int main (int argc, char** argv){
    if (argc != 3){
        printf("wrong number of arguments");
        return 1;
    }

    mkfifo("/tmp/integral_tmp",0666);
    int n = atoi(argv[2]);

    time_t begin, end;
    time(&begin);

    for (int i = 0; i < n; i++){
        int child_pid = fork();
        if (child_pid == 0){
            char i_string[BUFF_SIZE];
            snprintf(i_string,BUFF_SIZE,"%d",i);
            execl("./integralPart","integralPart", argv[1], argv[2], i_string,NULL);
        }
    }

    int file = open("/tmp/integral_tmp",O_RDONLY);

    int counter = 0;
    double result = 0.0;
    while (counter < n){
        char buff[BUFF_SIZE];
        int size = read(file, buff, BUFF_SIZE);
        buff[size] = 0;
        char *tmp_storage;
        tmp_storage = strtok(buff," ");
        while (tmp_storage != NULL){
            result += strtod(tmp_storage,NULL);
            tmp_storage = strtok(NULL," ");
            counter++;
        }

    }

    printf("dx: %s\n n: %d\n", argv[1],n);
    printf("Result: %f\n",result);

    time(&end);
    time_t elapsed = end - begin;
    printf("Time:%ld s\n", elapsed);

    return 0;
}
