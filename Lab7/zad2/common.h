
#ifndef LAB7_COMMON_H
#define LAB7_COMMON_H

#include <semaphore.h>

#ifdef POSIX
#define PROJECT_IDENTIFIER "SHARED"
    #define SEM_QUEUE_FNAME "/sem_queue"
    #define SEM_CHAIRS_FNAME "/sem_chairs"
    #define SEM_BARBERS_FNAME "/sem_barbers"
    #define SEM_BUFFER_MUTEX_FNAME "/sem_mutex"
#endif


#define BARBER_TOTAL 3
#define CHAIR_TOTAL 2
#define QUEUE_SIZE 5
#define CUSTOMERS_TOTAL 6
#define BUFFER_SIZE 4096

#endif //LAB7_COMMON_H
