/*
 ==============================================================================
 Name:              nodede.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 24/05/2017
 Copyright:         MIT License
 Description:       Node structures for using in linked lists
 ==============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "node.h"

struct nodes
{
    void*   data;
    node_t  *next;
    node_t  *previous;
};

// Cria um nodevo node
node_t* createNode(void *data)
{
    node_t *p = malloc(sizeof(node_t));

    if (p == NULL){
        perror("cria_node:");
        exit(EXIT_FAILURE);
    }

    p->data = data;
    p->next = NULL;
    p->previous = NULL;

    return p;
}

void connectNodes(node_t* sourceNode, node_t* node)
{
    if (fonte == NULL || destinode == NULL){
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    sourceNode->next = node;
    node->previous = sourceNode;
}

void disconnectNode(node_t *node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node->next = NULL;
    node->previous = NULL;
}

void desliga_node_previous (node_t *node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node->previous = NULL;
}

void desliga_node_next (node_t *node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    node->next = NULL;
}


void *obter_dado (node_t *node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return node->data;
}

node_t *obtem_next (node_t* node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return node->next;
}

node_t *obtem_previous (node_t *node)
{
    if (node == NULL) {
        fprintf(stderr,"liga_nodes: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

    return node->previous;
}
