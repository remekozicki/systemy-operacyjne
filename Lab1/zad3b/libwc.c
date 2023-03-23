#include "libwc.h"
#include <ctype.h>
#define SIZE 200

WCLibrary WCLibrary_create(size_t size){
    return (WCLibrary){
        .arr = calloc(size, sizeof(char *)),
        .active = calloc(size, sizeof(int)),
        .current_index = 0,
        .size = size,
    };
}

void WCLibrary_clear(WCLibrary* WCLibraryStruct){
    for (size_t i = 0; i < WCLibraryStruct->current_index; ++i) {
        if (WCLibraryStruct->active[i] == 1){
            free(WCLibraryStruct->arr[i]);
        }
    }
    WCLibraryStruct->current_index = 0;
//    wypełniam active 0  jako że nie są używane
    memset(WCLibraryStruct->active, 0, sizeof(int)*(WCLibraryStruct->size));
}

void WCLibrary_destroy(WCLibrary* WCLibraryStruct){
    WCLibrary_clear(WCLibraryStruct);
    free(WCLibraryStruct->active);
    free(WCLibraryStruct->arr);

}

void WCLibrary_pop(WCLibrary* WCLibraryStruct, size_t index){
    if (WCLibraryStruct->current_index < index){
        fprintf(stderr, "[WC LIB] Index out of range\n");
    }
    else if (WCLibraryStruct->active[index] == 0) {
        fprintf(stderr, "[WC LIB] Index is empty or removed\n");
    }
    else{
        free(WCLibraryStruct->arr[index]);
        WCLibraryStruct->active[index] = 0;
    }
}


char* WCLibrary_find_by_index(WCLibrary* WCLibraryStruct, int index){
    if (WCLibraryStruct->active[index] == 0) {
        fprintf(stderr, "[WC LIB] Index is empty or removed\n");
        return NULL;
    }else{
        return WCLibraryStruct->arr[index];
    }

}


void WCLibrary_word_counter(WCLibrary* WCLibraryStruct, char* input_filename){
    char file_path[] = "./tmp/temp.txt";
    char *command =calloc(SIZE,sizeof(char));

    for (int i = 0; i < SIZE; ++i) {
        command[i] = 0;
    }

    strcpy(command,"wc ");
    strcat(command,input_filename);
    strcat(command," > ");
    strcat(command,file_path);
    printf("%s",command);
    system(command);

    FILE* file = fopen(file_path,"r");
    if (file == NULL){
        fprintf(stderr, "[WC LIB] Cannot open the file\n");
        return;
    }
    fseek(file, 0, SEEK_END); // seeks to end of file
    long size = ftell(file); // Funkcja zwraca aktualną pozycję kursora odczytu/zapisu danych dla wskazanego strumienia czyli na dobrą sprawe długość
    fseek(file, 0, SEEK_SET ); // seek back to beginning of file

    char* buffer = calloc(size, sizeof(char));

    if (WCLibraryStruct->current_index < WCLibraryStruct->size){
        fread(buffer,sizeof(char),size,file);
        WCLibraryStruct->arr[WCLibraryStruct->current_index] = buffer;
        WCLibraryStruct->active[WCLibraryStruct->current_index] = 1;
        (WCLibraryStruct->current_index)++;
    }

    fclose(file);

}