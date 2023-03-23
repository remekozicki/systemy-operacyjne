
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char ** argv) {

    if (argc != 2){
        perror("wrong number of arguments");
        return 1;
    }

    pid_t child_pid;
    printf("PID glownego programu: %d\n", (int)getpid());

    int counter = argv[0][1];
    printf("%d",counter);


    for (int i = 0; i < counter; ++i) {

        if(child_pid!=0) {
            printf("Proces rodzica: Proces rodzica ma pid:%d\n", (int)getpid());
            printf("Proces rodzica: Proces dziecka ma pid:%d\n", (int)child_pid);
        } else {
            printf("Proces dziecka: Proces rodzica ma pid:%d\n",(int)getppid());
            printf("Proces dziecka: Proces dziecka ma pid:%d\n",(int)getpid());
        }

    }


    return 0;
}