
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <stdlib.h>

int main(int argc, char ** argv) {

    if (argc != 2){
        perror("wrong number of arguments");
        return 1;
    }

    int child_pid;
    int original_pid = (int)getpid();
    printf("PID glownego programu: %d\n", original_pid);
    int counter = atoi(argv[1]);
    for (int i = 0; i < counter; ++i) {
        child_pid = -1;

        if ((int)getpid() == original_pid){
            child_pid = fork();
        }
        if (child_pid == 0){
            printf("Proces rodzica ma pid:%d\n", (int)getppid());
            printf("Proces dziecka ma pid:%d\n", (int)getpid());
        }
    }
    while (wait(NULL) > 0);
    if ((int)getpid() == original_pid){

        printf("Proces macierzysty argv[1]:%s\n",argv[1]);
    }

    return 0;
}