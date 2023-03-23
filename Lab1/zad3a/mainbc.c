#include "libwc.h"
#include <stdio.h>
#include "dllmanager.h"
//#include "libwc.c"
#include <regex.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/times.h>
#include <stdlib.h>
#include <memory.h>
#include <unistd.h>
#include <dlfcn.h>



#define COMMAND_SIZE 2048

typedef enum {
    EXIT,
    WRONG_COMMAND,
    INIT,
    COUNT,
    SHOW,
    DESTROY,
    DELETE,

}Command;

WCLibrary WCObject;
int is_running = 1;  // 1 - true, 0 - false
Command id;
int num_input;
char path[COMMAND_SIZE];
int tmp;


void parse_input(char* arg1, char* arg2){
    if (strcmp(arg1, "init") == 0) {
        id = INIT;
        num_input = atoi(arg2);
    }
    else if (strcmp(arg1, "count") == 0){
        id = COUNT;
        strcpy(path,arg2);
    }
    else if (strcmp(arg1, "show") == 0){
        id = SHOW;
        num_input = atoi(arg2);
    }
    else if (strcmp(arg1, "delete") == 0){
        id = DELETE;
        num_input = atoi(arg2);
    }
    else if (strcmp(arg1, "destroy") == 0){
        id = DESTROY;
    }
    else if (strcmp(arg1, "exit") == 0){
        id = EXIT;
    }
    else{
        id = WRONG_COMMAND;
        fprintf(stderr,("Invalid command"));
    }
}


void read_command(){

    switch (id) {
        case INIT:
            WCObject = WCLibrary_create(num_input);
            break;
        case COUNT:
            WCLibrary_word_counter(&WCObject,path);
            break;
        case SHOW:
            printf("%s",WCLibrary_find_by_index(&WCObject,num_input));
            break;
        case DELETE:
            WCLibrary_pop(&WCObject,num_input);
            break;
        case DESTROY:
            WCLibrary_destroy(&WCObject);
            break;
        case EXIT:
            is_running = 0;
            break;
        case WRONG_COMMAND:
            fprintf(stderr, "Wrong command, try...:\n");
            fprintf(stderr, "count {path}\n");
            fprintf(stderr, "show {index >= 0}\n");
            fprintf(stderr, "delete {index >= 0}\n");
            fprintf(stderr, "destroy\n");
            break;

    }
}


double timeDifference(clock_t t1, clock_t t2){
    return ((double)(t2 - t1) / sysconf(_SC_CLK_TCK));
}

void writeResult(clock_t start, clock_t end,struct tms t_start,struct tms t_end){
    printf("\tREAL_TIME: %fl\n", timeDifference(start,end));
    printf("\tUSER_TIME: %fl\n", timeDifference(t_start.tms_utime, t_end.tms_utime));
    printf("\tSYSTEM_TIME: %fl\n", timeDifference(t_start.tms_stime, t_end.tms_stime));
}


int main(){

//    WCObject = malloc(sizeof(WCLibrary));
    load_dll("libwc.so");

    clock_t timeStart,timeEnd;
    struct tms tmsStart,tmsEnd;

    while (is_running == 1){
        printf("[WC] >> ");

        timeStart = times(&tmsStart);
        char* first_arg = calloc(200, sizeof(char));
        char* second_arg = calloc(200, sizeof(char));
        char* line = NULL;
        size_t line_len;

        tmp = getline(&line, &line_len, stdin);

        sscanf(line,"%s %s", first_arg, second_arg );

        parse_input(first_arg, second_arg);
        read_command();

        timeEnd=times(&tmsEnd);
        writeResult(timeStart, timeEnd,tmsStart, tmsEnd);

        free(line);
        free(second_arg);
        free(first_arg);


    }


}