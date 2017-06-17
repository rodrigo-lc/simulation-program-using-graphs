/*
 ==============================================================================
 Name:              queue.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Queue implementation using linked lists
 ==============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "../../include/linkedList/linkedList.h"
#include "../../include/linkedList/node.h"
#include "queue.h"

//#define DEBUG
#define FALSE 0
#define TRUE 1

struct queues{
	linkedList_t* list;
};

// Create a generic queue
queue_t* createQueue(void)
{
	queue_t* queue = (queue_t*) malloc(sizeof(queue_t));

    if (queue == NULL)
    {
        fprintf(stderr, "createQueue: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    queue->list = createLinkedList();

    return queue;
}

// Add element
void enqueue(void* data, queue_t* queue)
{
	node_t* node;

    if (queue == NULL)
    {
        fprintf(stderr, "enqueue: Invalid queue pointer!\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("enqueue: %x\n", data);
    #endif // DEBUG

    node = createNode(data);
    addTail(queue->list, node);
}

// Get first element
void* dequeue(queue_t* queue)
{
	node_t* node;
	void* data;

    if (queue == NULL)
    {
        fprintf(stderr, "dequeue: Invalid queue pointer!\n");
        exit(EXIT_FAILURE);
    }

    node = removeHead(queue->list);
    data = getData(node);
    free(node);

    return data;
}


void freeQueue(queue_t* queue)
{
    if (queue == NULL)
    {
        fprintf(stderr, "freeQueue: Invalid queue pointer! Impossible to free memory!\n");
        exit(EXIT_FAILURE);
    }

    if (!isListEmpty(queue->list))
    {
    	fprintf(stderr, "freeQueue: Impossible to free memory! Queue is not empty!\n");
		exit(EXIT_FAILURE);
    }

    free(queue->list);
    free(queue);
}

int isQueueEmpty(queue_t *queue)
{
    if (queue == NULL)
    {
        fprintf(stderr, "emptyQueue: Invalid queue pointer!\n");
        exit(EXIT_FAILURE);
    }

    return isListEmpty(queue->list);
}
