#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main( int argc, char ** argv){

    if(argc == 2) {
        FILE *mail;
        if (strcmp(argv[1], "nadawca") == 0) {
            mail = popen("mail | tail | sort -k 3", "w");

        } else if (strcmp(argv[1], "data") == 0) {
            mail = popen("mail | tail -n +2", "w");
        } else {
            printf("invalid argument");
            return 2;

        }
        pclose(mail);

    }else if( argc == 4){
        char command[1024];
        snprintf(command,1024,"mail -s \"%s\" %s",argv[2],argv[1]);
        FILE* mail=popen(command,"w");
        fwrite(argv[3],sizeof(char),strlen(argv[3]),mail);
        pclose(mail);
    }else{
        printf("wrong number of arguments");
        return 1;
    }



    return 0;

}
