#ifndef LISTA_ENC_H_INCLUDED
#define LISTA_ENC_H_INCLUDED

#include "node.h"

typedef struct linkedLists linkedList_t;

linkedList_t* createLinkedList(void);
void add_tail(linkedList_t *list, node_t* elemento);
node_t *obter_cabeca(linkedList_t *list);

int list_empty(linkedList_t *list);
node_t *remove_tail(linkedList_t *list);
node_t *remove_cabeca(linkedList_t *list);

void print_list (linkedList_t *list);
void print_list_tras (linkedList_t *list);

/* Retorna o dado de um node removido*
 * node_removido é liberado da memoória  */
void *remove_node(linkedList_t* list, node_t *node_removido);


#endif // LISTA_ENC_H_INCLUDED
