
#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct nodes    // Nodes for a doubly linked list
{
    void*   data;
    node_t* nextNode;
    node_t* previousNode;
};

node_t* createNode(void* data)
{
    node_t* node = malloc(sizeof(node_t));

    if (node == NULL)
    {
        perror("createNode:");
        exit(EXIT_FAILURE);
    }

    node->data = data;
    node->nextNode = NULL;
    node->previousNode = NULL;

    return node;
}

void connectNodes(node_t* sourceNode, node_t* node)
{
    if (sourceNode == NULL || node == NULL){
        fprintf(stderr, "connectNodes: Invalid nodes!");
        exit(EXIT_FAILURE);
    }

    sourceNode->nextNode = node;
    node->previousNode = sourceNode;
}

void disconnectNode(node_t *node)
{
    if (node == NULL) {
        fprintf(stderr, "disconnectNode: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    node->nextNode = NULL;
    node->previousNode = NULL;
}

void disconnectPreviousNode(node_t* node)
{
    if (node == NULL)
    {
        fprintf(stderr, "disconnectPreviousNode: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    node->previousNode = NULL;
}

void disconnectNextNode(node_t *node)
{
    if (node == NULL)
    {
        fprintf(stderr, "disconnectNextNode: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    node->nextNode = NULL;
}


void* getData(node_t* node)
{
    if (node == NULL)
    {
        fprintf(stderr, "getData: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return node->data;
}

node_t* getNext(node_t* node)
{
    if (node == NULL)
    {
        fprintf(stderr, "getNext: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return node->nextNode;
}

node_t* getPrevious(node_t* node)
{
    if (node == NULL)
    {
        fprintf(stderr, "getPrevious: Invalid pointer!");
        exit(EXIT_FAILURE);
    }

    return node->previousNode;
}
