/*
 ==============================================================================
 Name:              graph.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 24/05/2017
 Copyright:         MIT License
 Description:       Graphs using data structures such as: linked lists, stacks and
                    queues
 ==============================================================================
 */

// External includes
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

// Local includes
#include "graph.h"
#include "vertex.h"
#include "../../include/linkedList/linkedList.h"
#include "../../include/linkedList/node.h"
#include "../../include/queue/queue.h"
#include "../../include/stack/stack.h"

// Defines
#define FALSE       0
#define TRUE        1
#define INFINITO    INT_MAX
//#define DEBUG



struct graphs {
	int id;
	linkedList_t* vertex;
};


void bfs(graph_t* graph, vertex_t* inicial)
{




}


void dfs(graph_t* graph, vertex_t* inicial)
{





}

//--------------------------------------------------------------------------------------

graph_t *create_graph(int id)
{
	graph_t *p = NULL;

	p = (graph_t*) malloc(sizeof(graph_t));

	if (p == NULL)	{
		perror("create_graph:");
		exit(EXIT_FAILURE);
	}

	p->id = id;
	p->vertex = create_list_enc();

	return p;
}

vertex_t* graph_adicionar_vertex(graph_t *graph, int id)
{
	vertex_t* vertex;
	node_t *node;

#ifdef DEBUG
	printf("graph_adicionar_vertex: %d\n", id);
#endif

	if (graph == NULL)
    {
        fprintf(stderr,"graph_adicionar_vertex: graph invalido!");
        exit(EXIT_FAILURE);
	}

	if (searchVertex(graph, id) != NULL)
    {
		fprintf(stderr,"graph_adicionar_vertex: vertex duplicado!\n");
		exit(EXIT_FAILURE);
	}

	vertex = createVertex(id);
	node = createNode(vertex);

    addTail(graph->vertex, node);

	return vertex;
}

vertex_t* searchVertex(graph_t* graph, int ID)
{
	node_t* nodeList;
	vertex_t* vertex;
	int myID;

	if (graph == NULL)
    {
		fprintf(stderr,"procura_vertex: graph invalido!");
		exit(EXIT_FAILURE);
	}

	if (emptyList(graph->vertex) == TRUE)
		return FALSE;

	nodeList = getHead(graph->vertex);

	while (nodeList)
	{
		//obtem o endereco da list
		vertex = getData(nodeList);

		//obterm o id do vertex
		myID = vertexGetID(vertex);

		if (myID == ID) {
			return vertex;
		}

		nodeList = (nodeList);
	}

	return NULL;
}

void adiciona_adjacentes(graph_t *graph, vertex_t* vertex, int n, ...)
{
	va_list argumentos;
	vertex_t *sucessor;
	edges_t *edge;

	int id_sucessor;
	int weight;
        int x;

	/* Initializing arguments to store all values after num */
	va_start (argumentos, n);

	for (x = 0; x < n; x=x+2 )
	{
		id_sucessor = va_arg(argumentos, int);
		weight = va_arg(argumentos, int);

		sucessor = procura_vertex(graph, id_sucessor);

		if (sucessor == NULL) {
			fprintf(stderr, "adiciona_adjacentes: sucessor nao encontrado node graph\n");
			exit(EXIT_FAILURE);
		}

		edge = create_edge(vertex, sucessor,weight);
		adiciona_edge(vertex, edge);

#ifdef DEBUG
		printf("\tvertex: %d\n", vertex_get_id(vertex));
		printf("\tsucessor: %d\n", id_sucessor);
		printf("\tweight: %d\n", weight);
#endif

	}

	va_end (argumentos);
}

void exportGraphDot(const char* filename, graph_t* graph)
{
	FILE *file;

	node_t *node_vert;
	node_t *node_arest;
	vertex_t *vertex;
	vertex_t *adjacente;
	edges_t *edge;
	edges_t *contra_edge;
	linkedList_t *list_edges;

	int weight;

	if (filename == NULL || graph == NULL){
		fprintf(stderr, "export_grafp_dot: ponteiros invalidos\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "w");

	if (file == NULL){
		perror("export_grafp_dot:");
		exit(EXIT_FAILURE);
	}

	fprintf(file, "graph {\n");

	//obtem todos os nodes da list
	node_vert = obter_cabeca(graph->vertex);

	while (node_vert){
		vertex = obter_dado(node_vert);

		//obtem todos as edges
		list_edges = vertex_get_edges(vertex);

		node_arest = obter_cabeca(list_edges);
		while (node_arest) {
			edge = obter_dado(node_arest);

			//ignodera caso já exportada
			if (edge_get_status(edge) == EXPORTADA) {
				node_arest = obtem_next(node_arest);
				continue;
			}

			//marca como exportada esta edge
			edge_set_status(edge, EXPORTADA);
			adjacente = edge_get_adjacente(edge);

			//marca contra-edge também como exporta node caso de graph não direcionados
			contra_edge = procurar_adjacente(adjacente, vertex);
			edge_set_status(contra_edge, EXPORTADA);

			//obtem weight
			weight = edge_get_weight(edge);

			fprintf(file, "\t%d -- %d [label = %d];\n",
					vertex_get_id(vertex),
					vertex_get_id(adjacente),
                    weight);

			node_arest = obtem_next(node_arest);
		}
		node_vert = obtem_next(node_vert);
	}
	fprintf(file, "}\n");
	fclose(file);
}


void freeGraph (graph_t* graph){
	node_t *node_vert;
	node_t *node_arest;
	node_t *node_liberado;
	vertex_t *vertex;
	edges_t *edge;
	linkedList_t *list_edges;

	if (graph == NULL) {
		fprintf(stderr, "libera_graph: graph invalido\n");
		exit(EXIT_FAILURE);
	}

	//varre todos os vertexs
	node_vert = obter_cabeca(graph->vertex);
	while (node_vert){
		vertex = obter_dado(node_vert);

		//libera todas as edges
		list_edges = vertex_get_edges(vertex);
		node_arest = obter_cabeca(list_edges);
		while (node_arest){
			edge = obter_dado(node_arest);

			//libera edge
			free(edge);

			//libera node da lsita
			node_liberado = node_arest;
			node_arest = obtem_next(node_arest);
			free(node_liberado);
		}

		//libera list de edges e vertex
		free(list_edges);
		free(vertex);

		//libera node da list
		node_liberado = node_vert;
		node_vert = obtem_next(node_vert);
		free(node_liberado);
	}

	//libera graph e vertex
	free(graph->vertex);
	free(graph);
}
