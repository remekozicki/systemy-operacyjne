#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/shm.h>

#include "memory.h"


#ifdef POSIX
#include <errno.h>

static int get_memory(const char* filename, int size) {
    int descriptor = shm_open(filename, O_CREAT | O_RDWR, 0644);
    if (descriptor == -1) {
        return -1;
    }
    if(ftruncate(descriptor, size) == -1) {
        perror("[ERROR] ftruncate() call");
        return -1;
    }
    return descriptor;
}

char *attach_memory(const char* filename, int size) {
    int memory_id = get_memory(filename, size);
    if (memory_id == -1) {
        fprintf(stderr, "[ERROR] Can't get file descriptor for: %s\n", filename);
        return NULL;
    }
    char *shared_memory = (char*) mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, memory_id, 0);
    return shared_memory;
}

bool detach_memory(char *memory) {
    return (shmdt(memory) != -1);
}

bool destroy_memory(const char *filename) {
    return (shm_unlink(filename) != -1);
}
#endif

