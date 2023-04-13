#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFF_SIZE 1024

double f(double x){
    return 4/(x*x + 1);
}

int main(int argc, char ** argv){
    if(argc!=4){
        printf("invalid number of arguments");
        return 1;
    }
    int n = atoi(argv[2]);
    int i = atoi(argv[3]);
    double dx = strtod(argv[1],NULL);
    double rectangle_length = 1.0/n; // length of single rectangle
    double result = 0.0;
    double x = rectangle_length*i;
    double end = rectangle_length*(1+i);
    double steps = rectangle_length/dx;

    for (int j = 0; j < steps-1; ++j) {
        result += f(x)*dx;
        x+=dx;
    }
    result += f(x)*(end-x);

    char buff[BUFF_SIZE];
    snprintf(buff,BUFF_SIZE,"%lf",result);
    int file = open("/tmp/integral_tmp",O_WRONLY);
    write(file,buff, BUFF_SIZE);
    close(file);



    return 0;

}
