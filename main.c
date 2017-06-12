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
	int id;

	graph = create_graph(0);
	queue = create_queue();

	//Adiciona todos os vertexs node graph
	vertex = graphAddVertex(graph, 1);
	enqueue(vertex, queue);

/*
        // constrói graph
	while (!fila_empty(fila))	{
		vertex = dequeue(fila);
		id = vertex_get_id(vertex);

		switch(id){
			case 1:
				adiciona_adjacentes(graph, vertex, 6, 6, 14, 2, 7, 3, 9);
				break;
			case 2:
				adiciona_adjacentes(graph, vertex, 6, 1, 7, 3, 10, 4, 15);
				break;
			case 3:
				adiciona_adjacentes(graph, vertex, 8, 6, 2, 1, 9, 2, 10, 4, 11);
				break;
			case 4:
				adiciona_adjacentes(graph, vertex, 6, 5, 6, 3, 11, 2, 15);
				break;
			case 5:
				adiciona_adjacentes(graph, vertex, 4, 6, 9, 4, 6);
				break;
			case 6:
				adiciona_adjacentes(graph, vertex, 6, 1, 14, 3, 2, 5, 9);
				break;
			case 7:
				adiciona_adjacentes(graph, vertex, 2, 8, 9);
				break;
			case 8:
				adiciona_adjacentes(graph, vertex, 4, 7, 9, 9, 4);
				break;
			case 9:
				adiciona_adjacentes(graph, vertex, 2, 8, 4);
				break;
			case 10:
				adiciona_adjacentes(graph, vertex, 4, 11, 1, 12, 8);
				break;
			case 11:
				adiciona_adjacentes(graph, vertex, 4, 10, 1, 12, 4);
				break;
			case 12:
				adiciona_adjacentes(graph, vertex, 4, 11, 4, 10, 8);
				break;
			default:
				break;
		}
	}
*/
	export_graph_dot("graph.dot", graph);

	libera_fila(queue);
	libera_graph(graph);

	return EXIT_SUCCESS;
}

