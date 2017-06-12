#include <stdlib.h>
#include <stdio.h>

#include "../../include/linkedList/linkedList.h"
#include "../../include/linkedList/node.h"
#include "stack.h"

//#define DEBUG

#define FALSO 0
#define VERDADEIRO 1

struct stacks
{
	linkedList_t* list;
};


//cria uma pilha generica
stack_t* createStack(void)
{
    stack_t* stack = (stack_t*) malloc(sizeof(stack_t));

    if (stack == NULL) {
        fprintf(stderr, "Erro alocando dados em cria_pilha!\n");
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
        fprintf(stderr, "push: pilha invalida\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("push: %x\n", dado);
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
        fprintf(stderr, "pop: pilha invalida!\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    //printf("pop: %d\n", pilha->data[topo - 1]);
    #endif // DEBUG

    node = removeTail(stack->list);
    data = getData(node);
    free(node);

    return data;
}


void freeStack(stack_t* stack)
{
	if (stack == NULL) {
        fprintf(stderr, "Erro em libera_pilha\n");
        exit(EXIT_FAILURE);
    }

    if (!emptyList(stack->list))    {
    	fprintf(stderr, "Impossivel liberar pilha, ainda ha dados\n");
    	exit(EXIT_FAILURE);
    }

    free(stack->list);
    free(stack);

}

int emptyStack(stack_t* stack)
{
    if (stack == NULL)
    {
        fprintf(stderr, "pilha_vazia: pilha invalida\n");
        exit(EXIT_FAILURE);
    }

    return emptyList(stack->list);
}
