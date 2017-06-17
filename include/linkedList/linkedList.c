/*
 ==============================================================================
 Name:              linkedList.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Linked lists for data structures
 ==============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "linkedList.h"
#include "node.h"

//#define DEBUG
#define FALSE 0
#define TRUE 1

struct linkedLists {
    node_t* headNode;
    node_t* tailNode;
    int size;
};

//create uma list empty
linkedList_t* createLinkedList(void)
{
    linkedList_t* list = malloc(sizeof(linkedList_t));

    if (list == NULL)
    {
        perror("createLinkedList:");
        exit(EXIT_FAILURE);
    }

    list->headNode = NULL;
    list->tailNode = NULL;
    list->size = 0;

    return list;
}

void addTail(linkedList_t* list, node_t* node)
{
    if (list == NULL || node == NULL){
        fprintf(stderr,"addTail: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

   #ifdef DEBUG
   printf("Adicionando %p --- tamanho: %d\n", node, list->size);
   #endif // DEBUG

   // empty list
   if (list->size == 0)
   {
        #ifdef DEBUG
        printf("add_tail: add primeiro elemento: %p\n", node);
        #endif // DEBUG

        list->tailNode = node;
        list->headNode = node;
        list->size++;

        disconnectNode(node);
   }
   else
   {
        // Remove qualquer ligacao antiga
        disconnectNode(node);
        // Liga tail da list com nodevo elemento
        connectNodes(list->tailNode, node);

        list->tailNode = node;
        list->size++;
   }
}

void printList(linkedList_t* list)
{
    node_t* node = NULL;

    if (list == NULL)
    {
        fprintf(stderr, "printList: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    // Node list navegation to print list
    node = list->headNode;
    while (node)
    {
        printf("Data: %p\n", getData(node));
        node = getNext(node);
    }
}

void printListReverse(linkedList_t* list)
{
    node_t* node = NULL;

    if (list == NULL)
    {
        fprintf(stderr, "printListReverse: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    // Node list navegation to print list from tail to head
    node = list->tailNode;
    while (node)
    {
        printf("Data: %p\n", getData(node));
        node = getPrevious(node);
    }
}

int isListEmpty(linkedList_t* list)
{
	int returnValue;

	(list->size == 0) ? (returnValue = TRUE) : (returnValue = FALSE);

	return returnValue; // TRUE OR FALSE
}

node_t* getHead(linkedList_t* list){

	if (list == NULL)
    {
        fprintf(stderr, "getHead: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

	return list->headNode;
}

node_t* getTail(linkedList_t* list){

	if (list == NULL)
    {
		fprintf(stderr, "getTail: Invalid pointer!");
		exit(EXIT_FAILURE);
	}

	return list->tailNode;
}

node_t* removeTail(linkedList_t *list)
{
	node_t* previousNode;
	node_t* removedNode;

	if (list == NULL)
    {
	    fprintf(stderr, "removeTail: Invalid pointer!");
	    exit(EXIT_FAILURE);
	}

	if (list->tailNode == NULL)
		return NULL;

	removedNode = list->tailNode;

	if (list->tailNode == list->headNode) {
		list->size = 0;

		list->tailNode = NULL;
		list->headNode = NULL;

		return removedNode;
	}

	previousNode = getPrevious(list->tailNode);
	disconnectNode(removedNode);
	list->tailNode = previousNode;
	disconnectNode(previousNode);
	list->size--;

	return removedNode;
}

node_t* removeHead(linkedList_t* list)
{
	node_t* nextNode;
	node_t* removedNode;

	if (list == NULL)
    {
	    fprintf(stderr, "removeHead: Invalid pointer!");
	    exit(EXIT_FAILURE);
	}

	if (list->tailNode == NULL)
		return NULL;

	removedNode = list->headNode;

	if (list->tailNode == list->headNode) {
		list->size = 0;

		list->tailNode = NULL;
		list->headNode = NULL;

		return removedNode;
	}

	nextNode = getNext(list->headNode);
	disconnectNode(removedNode);
	list->headNode = nextNode;
	disconnectPreviousNode(nextNode);
	list->size--;

	return removedNode;
}

void* removeNode(linkedList_t* list, node_t* removedNode)
{
	node_t* myNode;
	void* data;

	node_t* nextNode;
	node_t* previousNode;

	if (list == NULL || removedNode == NULL)
    {
		fprintf(stderr, "removeNode: Invalid pointer!");
		exit(EXIT_FAILURE);
	}

	// Node list navegation
	myNode = getHead(list);
	while (myNode)
    {
		data = getData(myNode);

		if (myNode == removedNode)
        {

			if (myNode == list->headNode)
				removeHead(list);
			else if (myNode == list->tailNode)
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

