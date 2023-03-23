#include <stdio.h>
#include "libwc.c"

int main(){
    WCLibrary chararray = WCLibrary_create(10);
    WCLibrary_word_counter(&chararray, "main.c");
    printf("\n");
    printf("%s", WCLibrary_find_by_index(&chararray,0));
    return 0;
}