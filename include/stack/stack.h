/*
 ==============================================================================
 Name:              stack.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Stack implementation using linked lists - header file
 ==============================================================================
 */

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

typedef struct stacks stack_t;

stack_t* createStack(void);
void    push(void* data, stack_t* stack);
void*   pop(stack_t* stack);
void    freeStack(stack_t* stack);
int     isStackEmpty(stack_t* stack);

#endif // STACK_H_INCLUDED
