#include <stdio.h>
#include "libwc.c"
#include "dllmanager.h"
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
    CREATE,
    COUNT,
    FIND,
    DESTROY,
    DELETE,

}Command;

regex_t rCREATE;
regex_t rCOUNT;
regex_t rFIND;
regex_t rDESTROY;
regex_t rEXIT;
regex_t rDELETE;

WCLibrary WCObject;
int is_running = 1;  // 1 - true, 0 - false
Command id;\
int num_input;
char path[COMMAND_SIZE];
int tmp;

int to_regex(){
    int status = 0;
    status += regcomp(&rCREATE, "create [0-9][0-9]*", 0);
    status *= 10;
    status += regcomp(&rCOUNT, "count ..*", 0);
    status *= 10;
    status += regcomp(&rFIND, "find [0-9][0-9]*", 0);
    status *= 10;
    status += regcomp(&rDELETE, "delete [0-9][0-9]*", 0);
    status *= 10;
    status += regcomp(&rDESTROY, "destroy", 0);
    status *= 10;
    status += regcomp(&rEXIT, "exit", 0);
    return status;

}

size_t minFunc(size_t a, size_t b){
    if (a < b){
        return a;
    }else{
        return b;
    }
}

void parse_input(char* input, size_t input_len){
    if (regexec(&rCREATE, input, 0, NULL, 0) == 0) {
        id = CREATE;
        sscanf(input, "create %d", &num_input);
    }
    else if (regexec(&rCOUNT, input, 0, NULL, 0) == 0){
        id = COUNT;
        input += strlen("count ");
        size_t newline = strcspn(input, "\n");
        strncpy(path, input, minFunc(newline,COMMAND_SIZE));
    }
    else if (regexec(&rFIND, input, 0, NULL, 0) == 0){
        id = FIND;
        sscanf(input, "find %d", &num_input);

    }
    else if (regexec(&rDELETE, input, 0, NULL, 0) == 0){
        id = DELETE;
        sscanf(input, "delete %d", &num_input);
    }
    else if (regexec(&rDESTROY, input, 0, NULL, 0) == 0){
        id = DESTROY;
    }
    else if (regexec(&rEXIT, input, 0, NULL, 0) == 0){
        id = EXIT;
    }
    else{
        id = WRONG_COMMAND;
        fprintf(stderr,("Invalid command"));
    }
}


void read_command(){

    switch (id) {
        case CREATE:
            WCObject = WCLibrary_create(num_input);
            break;
        case COUNT:
            WCLibrary_word_counter(&WCObject,path);
            break;
        case FIND:
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
            fprintf(stderr, "find {index >= 0}\n");
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
    int regex_status = to_regex();

//    WCObject = malloc(sizeof(WCLibrary));

    clock_t timeStart,timeEnd;
    struct tms tmsStart,tmsEnd;

    for(;;){
        printf("[WC] >> ");

        timeStart = times(&tmsStart);

        char* line = NULL;
        size_t line_len;

        tmp = getline(&line, &line_len, stdin);





        parse_input(line, line_len);
        read_command();

        timeEnd=times(&tmsEnd);
        writeResult(timeStart, timeEnd,tmsStart, tmsEnd);

        free(line);


    }


}