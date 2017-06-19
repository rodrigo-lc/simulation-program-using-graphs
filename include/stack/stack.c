/*
 ==============================================================================
 Name:              stack.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Stack implementation using linked lists
 ==============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "../../include/linkedList/linkedList.h"
#include "../../include/linkedList/node.h"
#include "stack.h"

//#define DEBUG
#define FALSE 0
#define TRUE 1

struct stacks{
	linkedList_t* list;
};

//cria uma pilha generica
stack_t* createStack(void)
{
    stack_t* stack = (stack_t*) malloc(sizeof(stack_t));

    if (stack == NULL) {
        fprintf(stderr, "createStack: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    stack->list = createLinkedList();

    return stack;
}

//adiciona elemento
void push(void* data, stack_t* stack)
{
	node_t* node;

    if (stack == NULL) {
        fprintf(stderr, "push: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("push: %x\n", vertexGetID(data));
    #endif // DEBUG

    node = createNode(data);
    addTail(stack->list, node);
}

//retira elemento do topo
void* pop(stack_t* stack)
{
	node_t* node;
	void*   data;

    if (stack == NULL)
    {
        fprintf(stderr, "pop: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    node = removeTail(stack->list);
    data = getData(node);
    free(node);

    #ifdef DEBUG
    printf("pop: %d\n", vertexGetID(data));
    #endif

    return data;
}


void freeStack(stack_t* stack)
{
	if (stack == NULL)
    {
        fprintf(stderr, "freeStack: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    if (!isListEmpty(stack->list))
    {
    	fprintf(stderr, "freeStack: Impossible to free data, list is not empty!\n");
    	exit(EXIT_FAILURE);
    }

    free(stack->list);
    free(stack);

}

int isStackEmpty(stack_t* stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "isStackEmpty: Invalid pointer!\n");
        exit(EXIT_FAILURE);
    }

    return isListEmpty(stack->list);
}
