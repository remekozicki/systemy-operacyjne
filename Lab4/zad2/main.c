#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

extern int errno;
void info(int signo, siginfo_t* siginfo, void* context){
    printf("singal: %d\n",siginfo->si_signo);
    printf("PID: %d\n",siginfo->si_pid);
    printf("exit value or signal: %x\n",siginfo->si_status);
    printf("Number of attempted system call: %d\n",siginfo->si_syscall);
    printf("Real user ID: %d\n",siginfo->si_uid);
}


void child(int signo, siginfo_t* siginfo, void* context){
    printf("child terminated\n");
}

void test1_SA_SIGINFO(struct sigaction new_action){
    new_action.sa_sigaction = info;
    new_action.sa_flags = SA_SIGINFO;

    sigemptyset(&new_action.sa_mask);
    sigaction(SIGUSR1,&new_action,NULL);

    printf("self:\n");

    kill(getpid(),SIGUSR1);
    printf("\n");
    printf("child:\n");

    int child_pid = fork();
    if (child_pid == 0){
        kill(getpid(), SIGUSR1);
        exit(0);
    }
    else{
        wait(NULL);
    }

    printf("\n");
    printf("Custom:\n");

    sigval_t val={10};
    sigqueue(getpid(),SIGUSR1,val);
};

void test2_SA_NOCLDSTOP(struct sigaction new_action){
    new_action.sa_sigaction = child;
    new_action.sa_flags = SA_NOCLDSTOP;

    sigemptyset(&new_action.sa_mask);
    sigaction(SIGCHLD,&new_action,NULL);

    int child_pid = fork();
    if (child_pid != 0){
        kill(child_pid, SIGSTOP);
    }
    else{
        wait(NULL);
    }

};

void test3_SA_NODEFER(struct sigaction new_action){
    sigemptyset(&new_action.sa_mask);
    new_action.sa_sigaction = child;
    new_action.sa_flags = SA_NODEFER;
    sigaction(SIGCHLD,&new_action,NULL);
    int child_pid = fork();
    if (child_pid != 0){
        kill(child_pid, SIGSTOP);
    }
    else{
        wait(NULL);
    }
    pause();
} ;



int main(){
    struct sigaction new_action;
    printf("test1: \n");
    test1_SA_SIGINFO(new_action);
    wait(NULL);
    printf("\n");
    printf("test2: \n");
    test2_SA_NOCLDSTOP(new_action);
    printf("test3: \n");
    test3_SA_NODEFER(new_action);
    wait(NULL);
    return 0;
}