/*
 ==============================================================================
 Name:              linkedList.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Linked lists for data structures - header file
 ==============================================================================
 */

#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include "node.h"

typedef struct linkedLists linkedList_t;

linkedList_t* createLinkedList(void);
node_t* getHead(linkedList_t* list);
node_t* getTail(linkedList_t* list);
node_t* removeTail(linkedList_t* list);
node_t* removeHead(linkedList_t* list);
int isListEmpty(linkedList_t* list);
int listGetSize(linkedList_t* list);
void addTail(linkedList_t* list, node_t* node);
void printList(linkedList_t* list);
void printInvertedList(linkedList_t* list);
void* removeNode(linkedList_t* list, node_t* removedNode); // return data from node and remove node from memory

#endif // linkedList_H_INCLUDED
