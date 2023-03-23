#ifndef _LIB_H_
#define _LIB_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ** arr;
    size_t current_index;
    size_t size;
    int* active;
} WCLibrary;

WCLibrary WCLibrary_create(size_t size);

void WCLibrary_clear(WCLibrary* WCLibraryStruct);

void WCLibrary_destroy(WCLibrary* WCLibraryStruct);

void WCLibrary_pop(WCLibrary* WCLibraryStruct, size_t index);

char* WCLibrary_find_by_index(WCLibrary* WCLibraryStruct, int index);

void WCLibrary_word_counter(WCLibrary* WCLibraryStruct, char* input_filename);

#endif


