#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/times.h>


double timeDifference(clock_t t1, clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void writeResult(clock_t start, clock_t end,struct tms t_start,struct tms t_end){
    printf("\tREAL_TIME: %fl\n", timeDifference(start,end));
    printf("\tUSER_TIME: %fl\n", timeDifference(t_start.tms_utime, t_end.tms_utime));
    printf("\tSYSTEM_TIME: %fl\n", timeDifference(t_start.tms_stime, t_end.tms_stime));
}


void zad1a(char ** argv){
    FILE *read_file = fopen(argv[3], "r");
    FILE *write_file = fopen(argv[4],"w");
    char c;
    int arg1;
    int arg2;
    sscanf(argv[1],"%d",&arg1);
    sscanf(argv[2],"%d",&arg2);

    for(c = fgetc(read_file); c != EOF; c = fgetc(read_file)){

        if (c == arg1){
            c = arg2;
        }
        fwrite(&c, sizeof(char), 1, write_file);
    }
    fclose(read_file);
    fclose(write_file);

}

void zad1b(char ** argv){

    int read_file = open(argv[3],O_RDONLY);
    int write_file = open(argv[4],O_WRONLY|O_CREAT);

    char c;
    int arg1;
    int arg2;

    sscanf(argv[1],"%d",&arg1);
    sscanf(argv[2],"%d",&arg2);

    while (read(read_file,&c,1)==1){
        if (c == arg1){
            c = arg2;
        }
        write(write_file,&c,1);
    }
    close(read_file);
    close(write_file);
}


int main(int argc, char ** argv){
    clock_t timeStart,timeEnd;
    static struct tms tmsStart,tmsEnd;
    if(argc!=5){
        printf("wrong number of arguments\n");
        return 1;
    }
    timeStart=0;
    timeEnd=0;
    timeStart=times(&tmsStart);
#ifndef SYS
    zad1b(argv);
#else
    zad1a(argv);
#endif
    timeEnd=times(&tmsEnd);
    writeResult(timeStart, timeEnd,
                tmsStart, tmsEnd);
    return 0;
}