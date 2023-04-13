#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#define BUFF_SIZE 1024


double f(double x){
    return 4/(x*x + 1);
}

double integral( double dx, int i, double rectangle_length){
    double steps,end,result = 0,x;
    x = rectangle_length*i;
    end = rectangle_length*(i+1);
    steps = rectangle_length/dx;
    for (int j = 0; j < steps-1; ++j) {
        result += f(x)*dx;
        x+=dx;
    }
    result += f(x)*(end-x);
    return result;
}

int main (int argc, char** argv){

    if (argc != 3){
        printf("wrong number of arguments");
        return 1;
    }
    double dx = strtod(argv[1],NULL);
    int n = atoi(argv[2]);
    double rectangle_length = 1.0/n; // length of single rectangle
    double result = 0.0;
    int fd[n][2];

    time_t begin, end;
    time(&begin);

    for (int i = 0; i < n; ++i) {
        pipe(fd[i]);
        int child_pid = fork();
        if (child_pid == 0){
            close(fd[i][0]);
            char c[BUFF_SIZE];
            snprintf(c, BUFF_SIZE, "%lf", integral(dx,i,rectangle_length));
            write(fd[i][1],c, strlen(c));
            exit(0);
        }else{
            close(fd[i][1]);
        }
    }

    while (wait(NULL)>0);
    for (int i = 0; i < n; ++i) {
        close(fd[i][1]);
        char buff[BUFF_SIZE];
        int size = read(fd[i][0],buff,BUFF_SIZE);
        buff[size] = 0;
        result += strtod(buff,NULL);
    }
    printf("dx: %s\n n: %d\n", argv[1],n);
    printf("Result: %f\n",result);

    time(&end);
    time_t elapsed = end - begin;
    printf("Time:%ld s\n", elapsed);

    return 0;
}