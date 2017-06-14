#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "node.h"

typedef struct linkedLists linkedList_t;

linkedList_t* createLinkedList(void);
void addTail(linkedList_t *list, node_t* element);
node_t* getHead(linkedList_t* list);

int emptyList(linkedList_t* list);
node_t* removeTail(linkedList_t* list);
node_t* removeHead(linkedList_t* list);

void printList(linkedList_t *list);
void printInvertedList(linkedList_t *list);

/* Retorna o dado de um node removido*
 * node_removido é liberado da memoória  */
void* removeNode(linkedList_t* list, node_t* removedNode);

#endif // LISTA_ENC_H_INCLUDED
