#ifndef __SHARED_MEMORY_H__
#define __SHARED_MEMORY_H__

#include <stdbool.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char *attach_memory(const char* filename, int size);
bool detach_memory(char *memory);
bool destroy_memory(const char *filename);

#endif