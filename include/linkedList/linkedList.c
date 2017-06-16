/*
 ==============================================================================
 Name:              linkedList.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 24/05/2017
 Copyright:         MIT License
 Description:       Vertex structures for using in applications using graphs
 ==============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "node.h"

#define FALSE 0
#define TRUE 1

//#define DEBUG

struct linkedLists {
    node_t* head;
    node_t* tail;
    int size;
};

//create uma list empty
linkedList_t* createLinkedList(void) {
    linkedList_t* list = malloc(sizeof(linkedList_t));

    if (list == NULL)
    {
        perror("create_list_enc:");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void addTail(linkedList_t* list, node_t* node)
{
    if (list == NULL || node == NULL){
        fprintf(stderr,"add_tail: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

   #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", node, list->size);
   #endif // DEBUG

   //list empty
   if (list->size == 0)
   {
        #ifdef DEBUG
        printf("add_tail: add primeiro elemento: %p\n", node);
        #endif // DEBUG

        list->tail = node;
        list->head = node;
        list->size++;

        disconnectNode(node);
   }
   else {
        // Remove qualquer ligacao antiga
        disconnectNode(node);
        // Liga tail da list com nodevo elemento
        connectNodes(list->tail, node);

        list->tail = node;
        list->size++;
   }
}

void printList (linkedList_t *list)
{
    node_t* node = NULL;

    if (list == NULL){
        fprintf(stderr,"print_list: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node = list->head;

    while (node){
        printf("Dados: %p\n", getData(node));

        node = getNext(node);
    }
}

void print_list_tras (linkedList_t *list)
{
    node_t *node = NULL;

    if (list == NULL){
        fprintf(stderr,"print_list: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node = list->tail;

    while (node){
        printf("Dados: %p\n", getData(node));

        node = getHead(node);
    }
}

int emptyList(linkedList_t* list)
{
	int returnValue;

	(list->size == 0) ? (returnValue = TRUE) : (returnValue = FALSE);

	return returnValue; // TRUE OR FALSE
}

node_t* getHead(linkedList_t* list){

	if (list == NULL)
    {
        fprintf(stderr,"obter_cabeca: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

	return list->head;
}

node_t* getTail(linkedList_t* list){

	if (list == NULL)
    {
		fprintf(stderr,"obter_cabeca: ponteiros invalidos");
		exit(EXIT_FAILURE);
	}

	return list->tail;
}

node_t* removeTail(linkedList_t *list)
{
	node_t* previousNode;
	node_t* removedNode;

	if (list == NULL){
	    fprintf(stderr,"remover_tail: ponteiro invalido");
	    exit(EXIT_FAILURE);
	}

	if (list->tail == NULL)
		return NULL;

	removedNode = list->tail;

	if (list->tail == list->head) {
		list->size = 0;

		list->tail = NULL;
		list->head = NULL;

		return removedNode;
	}

	previousNode = getPrevious(list->tail);
	disconnectNode(removedNode);
	list->tail = previousNode;
	disconnectNode(previousNode);
	list->size--;

	return removedNode;
}

node_t* removeHead(linkedList_t* list)
{
	node_t* nextNode;
	node_t* removedNode;

	if (list == NULL){
	    fprintf(stderr,"remover_tail: ponteiro invalido");
	    exit(EXIT_FAILURE);
	}

	if (list->tail == NULL)
		return NULL;

	removedNode = list->head;

	if (list->tail == list->head) {
		list->size = 0;

		list->tail = NULL;
		list->head = NULL;

		return removedNode;
	}

	nextNode = getNext(list->head);
	disconnectNode(removedNode);
	list->head = nextNode;
	disconnectPreviousNode(nextNode);
	list->size--;


	return removedNode;
}

void* removeNode(linkedList_t *list, node_t* removedNode)
{
	node_t* myNode;
	void* data;

	node_t* nextNode;
	node_t* previousNode;

	if (list == NULL || removedNode == NULL){
		fprintf(stderr,"remover_node: ponteiro invalido");
		exit(EXIT_FAILURE);
	}

	//Varre list até encontrar nó
	myNode = getHead(list);

	while (myNode)
        {
		data = getData(myNode);

		if (myNode == removeHead)
            {

			if (myNode == list->head)
				removeHead(list);
			else if (myNode == list->tail)
				removeHead(list);
			else
			{
				nextNode = getNext(myNode);
				previousNode = getPrevious(myNode);
				connectNodes(previousNode, nextNode);
				list->size--;
			}
			free(myNode);
			break;
		}
		myNode = getNext(myNode);
	}

	return data;
}

