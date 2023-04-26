
#ifndef LAB7_COMMON_H
#define LAB7_COMMON_H

#include <semaphore.h>

#ifdef SYSTEM_V
#define PROJECT_IDENTIFIER getenv("HOME")
    #define SEM_QUEUE_FNAME "0"
    #define SEM_CHAIRS_FNAME "1"
    #define SEM_BARBERS_FNAME "2"
    #define SEM_BUFFER_MUTEX_FNAME "3"
#endif


#define BARBER_TOTAL 3
#define CHAIR_TOTAL 2
#define QUEUE_SIZE 5
#define CUSTOMERS_TOTAL 6
#define BUFFER_SIZE 4096

#endif //LAB7_COMMON_H
