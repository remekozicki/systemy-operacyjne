#include<stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int count = 2;

void counter(int signo){
    printf("sygnal przyszedl\n");
    count+=1;
}

int main (int argc, char ** argv){

    if (argc < 3){
        perror("wrong number of arguments");
        return 1;
    }

    int catch_pid = atoi(argv[1]);
    int function;

    signal(SIGUSR1,counter);
    printf("%d:\n",catch_pid);

    fflush(stdout);

    for (int i = 2; i < argc; ++i) {
        function = atoi(argv[1]);
        sigval_t val = {function};
        sigqueue(catch_pid,SIGUSR1,val);

        printf("signal send\n");

        fflush(stdout);

        pause();

        fflush(stdout);
    }

    return 0;
}