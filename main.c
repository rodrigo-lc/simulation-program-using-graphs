/*
 =============================================================================
 Name:              main.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        16/06/2017
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description :      Simulation Program Using Graphs
 =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/stack/stack.h"
#include "include/queue/queue.h"
#include "include/graph/graph.h"

#define DEBUG

int main(void)
{
	graph_t*    graph;
	linkedList_t* list; //test liist

	graph = createGraph(0);
	list = createLinkedList();
	//exportGraphDot("graph.dot", graph);
    list = buildGraph(graph, "graphTest.dot");


	freeGraph(graph);



	return EXIT_SUCCESS;
}

