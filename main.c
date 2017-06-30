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
#include "include/component/component.h"

//#define DEBUG

int main(void)
{
	graph_t*    graph;
	vertex_t*   vertex;

	graph = createGraph(0);

	// exportGraphDot("graph.dot", graph);

    linkedList_t* componentsList = buildGraph(graph, "new 1.dot");

    vertex = searchVertex(graph, 6);
    linkedList_t* loopsList = loopSearch(graph, vertex);

    printLoops(loopsList);
    calculateCircuit(loopsList, componentsList);
    //printResults(componentsList);

    // implementar freeLinkedList
	freeGraph(graph);

    return EXIT_SUCCESS;
}

