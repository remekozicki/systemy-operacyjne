
#ifndef ZAD2_DLLMANAGER_H
#define ZAD2_DLLMANAGER_H

#ifdef USE_DLL
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "libwc.h"
#define WCLIB_SYMBOL_TABLE_SIZE 7

void load_dll(const char *path){
    void *handle = dlopen(path, RTLD_LAZY);

    if(handle==NULL){
        return;
    }

    *(void **) (&WCLibrary_create) = dlsym(handle,"WCLibrary_create");
    *(void **) (&WCLibrary_clear) = dlsym(handle,"WCLibrary_clear");
    *(void **) (&WCLibrary_destroy) = dlsym(handle,"WCLibrary_destroy");
    *(void **) (&WCLibrary_find_by_index) = dlsym(handle,"WCLibrary_find_by_index");
    *(void **) (&WCLibrary_word_counter) = dlsym(handle,"WCLibrary_word_counter");
    *(void **) (&WCLibrary_pop) =  dlsym(handle,"WCLibrary_pop");
}

#else
void load_dll(const char * file){}
#endif

#endif //ZAD2_DLLMANAGER_H
