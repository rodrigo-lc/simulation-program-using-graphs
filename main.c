/*
 =============================================================================
 Name        : graphs.c
 Author      :
 Version     :
 Copyright   : Renan Augusto Starke, todos os direitos reservados
 Description : graphs com list encadeadas, Ansi-style
             : estruturas disponiveis:
             : pilha e fila
 =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#include "include/stack/stack.h"
#include "include/queue/queue.h"
#include "include/graph/graph.h"

int main(void)
{
	graph_t*    graph;
	vertex_t*   vertex;
	queue_t*    queue;
	int ID, i;

	graph = createGraph(0);
	queue = createQueue();

	//Adiciona todos os vertexs node graph
	for(i=1; i<14; i++)
    {
        vertex = graphAddVertex(graph, i);
        enqueue(vertex, queue);
        printVertex(vertex);
    }

    // constrói graph
	while (!emptyQueue(queue))
    {
		vertex = dequeue(queue);
        ID = vertexGetID(vertex);

		switch(ID){
			case 1:
				addAdjacents(graph, vertex, 6, 6, 14, 2, 7, 3, 9);
				break;
			case 2:
				addAdjacents(graph, vertex, 6, 1, 7, 3, 10, 4, 15);
				break;
			case 3:
				addAdjacents(graph, vertex, 8, 6, 2, 1, 9, 2, 10, 4, 11);
				break;
			case 4:
				addAdjacents(graph, vertex, 6, 5, 6, 3, 11, 2, 15);
				break;
			case 5:
				addAdjacents(graph, vertex, 4, 6, 9, 4, 6);
				break;
			case 6:
				addAdjacents(graph, vertex, 6, 1, 14, 3, 2, 5, 9);
				break;
			case 7:
				addAdjacents(graph, vertex, 2, 8, 9);
				break;
			case 8:
				addAdjacents(graph, vertex, 4, 7, 9, 9, 4);
				break;
			case 9:
				addAdjacents(graph, vertex, 2, 8, 4);
				break;
			case 10:
				addAdjacents(graph, vertex, 4, 11, 1, 12, 8);
				break;
			case 11:
				addAdjacents(graph, vertex, 4, 10, 1, 12, 4);
				break;
			case 12:
				addAdjacents(graph, vertex, 4, 11, 4, 10, 8);
				break;
			default:
				break;
		}
    }

	exportGraphDot("graph.dot", graph);

	//freeQueue(queue);
	//freeGraph(graph);


	return EXIT_SUCCESS;
}

