#include <stdlib.h>
#include <stdio.h>

#include "../../include/linkedList/linkedList.h"
#include "../../include/linkedList/node.h"
#include "queue.h"

#define FALSO 0
#define VERDADEIRO 1

struct queues
{
	linkedList_t* list;
};


//cria uma pilha generica
queue_t* createQueue(void)
{
	queue_t* queue = (queue_t*) malloc(sizeof(queue_t));

    if (queue == NULL)
    {
        fprintf(stderr, "Erro alocando elements em cria_fila!\n");
        exit(EXIT_FAILURE);
    }

    queue->list = createLinkedList();

    return queue;
}


//adiciona elemento
void enqueue(void* data, queue_t *queue)
{
	node_t *node;

    if (queue == NULL) {
        fprintf(stderr, "push: pilha invalida\n");
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    printf("enqueue: %x\n", dado);
    #endif // DEBUG

    node = createNode(data);
    addTail(queue->list, node);
}

//retira elemento do topo
void *dequeue(queue_t *queue)
{
	node_t *node;
	void *dado;

    if (queue == NULL){
        fprintf(stderr, "dequeue: queue invalida!\n");
        exit(EXIT_FAILURE);
    }

    node = remover_cabeca(queue->list);
    dado = obter_dado(node);
    free(node);

    return dado;
}


void freeQueue(queue_t* queue)
{
    if (queue == NULL) {
        fprintf(stderr, "Erro em libera_fila\n");
        exit(EXIT_FAILURE);
    }

    if (!emptyList(queue->list)){
    	fprintf(stderr, "Impossivel liberar queue, ainda ha elements\n");
		exit(EXIT_FAILURE);
    }

    free(queue->list);
    free(queue);
}

int emptyQueue(queue_t *queue)
{
    if (queue == NULL) {
        fprintf(stderr, "queue_vazia: queue invalida\n");
        exit(EXIT_FAILURE);
    }

    return emptyList(queue->list);
}
