
#ifndef LAB7_SEM_H
#define LAB7_SEM_H

#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>

#ifdef SYSTEM_V
typedef int Semaphore;
#endif

Semaphore create_semaphore(const char *filename, int initial);
Semaphore open_semaphore(const char *filename);
void close_semaphore(Semaphore sem);
void unlink_semaphore(const char* filename);
void aquire(Semaphore sem);
void release(Semaphore sem);

#endif //LAB7_SEM_H
