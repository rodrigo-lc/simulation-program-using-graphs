/*
 ==============================================================================
 Name:              node.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 24/05/2017
 Copyright:         MIT License
 Description:       Node structures for using in linked lists - header file
 ==============================================================================
 */

#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

typedef struct nodes node_t;

node_t* createNode(void *data);
node_t* getNext(node_t* node);
node_t* getPrevious(node_t* node);
void* getData(node_t* node);
void connectNodes(node_t* sourceNode, node_t* destinyNode);
void disconnectNode(node_t* node);
void disconnectPreviousNode(node_t* node);
void disconnectNextNode(node_t* node);

#endif // NODE_H_INCLUDED
