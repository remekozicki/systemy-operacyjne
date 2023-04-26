#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/shm.h>

#include "memory.h"

#ifdef SYSTEM_V
static int get_memory(const char *filename, int size) {
    key_t key = ftok(filename, 0);
    if (key == -1) {
        return -1;
    }
    return shmget(key, size, 0644 | IPC_CREAT);
}

char *attach_memory(const char* filename, int size) {
    int memory_id = get_memory(filename, size);
    char *memory;
    if (memory_id == -1) {
        fprintf(stderr, "[ERROR] No identifier for file: %s\n", filename);
        return NULL;
    }
    memory = shmat(memory_id, NULL, 0);
    if (memory == (char*)(-1)) {
        fprintf(stderr, "[ERROR] Failed to load block with id %d\n", memory_id);
        return NULL;
    }
    return memory;
}

bool detach_memory(char *memory) {
    return (shmdt(memory) != -1);
}

bool destroy_memory(const char *filename) {
    int memory_id = get_memory(filename, 0);
    if(memory_id == -1) {
        return false;
    }
    return (shmctl(memory_id, IPC_RMID, NULL) != -1);
}
#endif

