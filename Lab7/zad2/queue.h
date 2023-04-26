
#ifndef LAB7_QUEUE_H
#define LAB7_QUEUE_H

#include <stdbool.h>

char queue_pop(char *queue);
void queue_push(char *queue, char byte);
bool queue_full(char *queue);
bool queue_empty(char *queue);

#endif //LAB7_QUEUE_H
