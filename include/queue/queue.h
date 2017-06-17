/*
 ==============================================================================
 Name:              queue.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Queue implementation using linked lists - header file
 ==============================================================================
 */

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

typedef struct queues queue_t;

queue_t* createQueue(void);
void    enqueue(void* data, queue_t* queue);
void*   dequeue(queue_t* queue);
void    freeQueue(queue_t* queue);
int     isQueueEmpty(queue_t* queue);

#endif // QUEUE_H_INCLUDED
