/*
 =============================================================================
 Name:              main.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        16/06/2017
 Version:           1.0
 Last modification: 20/06/2017
 Copyright:         MIT License
 Description :      Simulation Program Using Graphs
 =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/stack/stack.h"
#include "include/queue/queue.h"
#include "include/graph/graph.h"
#include "include/linkedList/linkedList.h"

//#define DEBUG

int main(void)
{
	graph_t*    graph;
	vertex_t*   vertex;
	stack_t* list;
	int i;

	graph = createGraph(0);

	// exportGraphDot("graph.dot", graph);

    list = buildGraph(graph, "graphTest.dot");

    vertex = searchVertex(graph, 6);
    linkedList_t* loopsList = loopSearch(graph, vertex);
    i = listGetSize(loopsList);
    printf("\nSize = %i",i);


    // implementar freeLinkedList
	freeGraph(graph);

    return EXIT_SUCCESS;
}

