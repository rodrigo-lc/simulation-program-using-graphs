#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

typedef struct queues queue_t;

queue_t* createQueue(void);

void    enqueue(void *data, queue_t *queue);
void*   dequeue(queue_t *queue);
int     emptyQueue(queue_t *queue);
void    freeQueue(queue_t* queue);

#endif // FILA_H_INCLUDED
