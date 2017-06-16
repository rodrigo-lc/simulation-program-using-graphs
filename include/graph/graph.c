/*
 ==============================================================================
 Name:              graph.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 14/06/2017
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
#define INFINITE    INT_MAX
#define DEBUG

struct graphs {
	int ID;
	linkedList_t* vertexList;
};

//--------------------------------------------------------------------------------------

graph_t* createGraph(int ID)
{
	graph_t* graph = NULL;

	graph = (graph_t*) malloc(sizeof(graph_t));

	if (graph == NULL)	{
		perror("create_graph:");
		exit(EXIT_FAILURE);
	}

	graph->ID = ID;
	graph->vertexList = createLinkedList();

	return graph;
}

vertex_t* graphAddVertex(graph_t* graph, int ID)
{
	vertex_t* vertex;
	node_t* node;

#ifdef DEBUG
	printf("graph_adicionar_vertex: %d\n", ID);
#endif

	if (graph == NULL)
    {
        fprintf(stderr,"graph_adicionar_vertex: graph invalido!");
        exit(EXIT_FAILURE);
	}

	if (searchVertex(graph, ID) != NULL)
    {
		fprintf(stderr,"graph_adicionar_vertex: vertex duplicado!\n");
		exit(EXIT_FAILURE);
	}

	vertex = createVertex(ID);
	node = createNode(vertex);

    addTail(graph->vertexList, node);

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

	if (emptyList(graph->vertexList) == TRUE)
		return FALSE;

	nodeList = getHead(graph->vertexList);

	while (nodeList)
	{
		//obtem o endereco da list
		vertex = getData(nodeList);

		//obterm o id do vertex
		myID = vertexGetID(vertex);

		if (myID == ID) {
			return vertex;
		}

		nodeList = getNext(nodeList);
	}

	return NULL;
}

void addAdjacents(graph_t *graph, vertex_t* vertex, int n, ...)
{
	va_list arguments;
	vertex_t* nextVertex;
	edges_t* edge;

	int nextID;
	int weight;
    int x;

	/* Initializing arguments to store all values after num */
	va_start (arguments, n);

	for (x = 0; x < n; x=x+2 )
	{
		nextID = va_arg(arguments, int);
		weight = va_arg(arguments, int);

		nextVertex = searchVertex(graph, nextID);

		if (nextVertex == NULL) {
			fprintf(stderr, "adiciona_adjacentes: sucessor nao encontrado node graph\n");
			exit(EXIT_FAILURE);
		}

		edge = createEdge(vertex, nextVertex, weight);
		addEdge(vertex, edge);

#ifdef DEBUG
		printf("\tvertex: %d\n", vertexGetID(vertex));
		printf("\tsucessor: %d\n", nextID);
		printf("\tweight: %d\n", weight);
#endif

	}

	va_end (arguments);
}

void exportGraphDot(const char* filename, graph_t* graph)
{
	FILE* file;

	node_t* vertexNode;
	node_t* edgeNode;
	vertex_t* vertex;
	vertex_t* adjacentVertex;
	edges_t* edge;
	edges_t* counterEdge;
	linkedList_t* edgeList;

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
	vertexNode = getHead(graph->vertexList);

	while (vertexNode){
		vertex = getData(vertexNode);

		//obtem todos as edges
		edgeList = vertexGetEdges(vertex);

		edgeNode = getHead(edgeList);
		while (edgeNode) {
			edge = getData(edgeNode);

			//ignodera caso já exportada
			if (edgeGetStatus(edge) == EXPORTADA) {
				edgeNode = getNext(edgeNode);
				continue;
			}

			//marca como exportada esta edge
			edgeSetStatus(edge, EXPORTADA);
			adjacentVertex = edgeGetAdjacent(edge);

			//marca contra-edge também como exporta node caso de graph não direcionados
			counterEdge = searchAdjacent(adjacentVertex, vertex);
			edgeSetStatus(counterEdge, EXPORTADA);

			//obtem weight
			weight = edgeGetWeight(edge);

			fprintf(file, "\t%d -- %d [label = %d];\n",
					vertexGetID(vertex),
					vertexGetID(adjacentVertex),
                    weight);

			edgeNode = getNext(edgeNode);
		}
		vertexNode = getNext(vertexNode);
	}
	fprintf(file, "}\n");
	fclose(file);
}


void freeGraph(graph_t* graph)
{
	node_t* vertexNode;
	node_t* edgeNode;
	node_t* freeNode;
	vertex_t* vertex;
	edges_t* edge;
	linkedList_t* edgeList;

	if (graph == NULL) {
		fprintf(stderr, "libera_graph: graph invalido\n");
		exit(EXIT_FAILURE);
	}

	//varre todos os vertexs
	vertexNode = getHead(graph->vertexList);
	while (vertexNode){
		vertex = getData(vertexNode);

		//libera todas as edges
		edge = vertexGetEdges(vertex);
		edgeNode = getHead(edgeList);
		while (edgeNode){
			edge = getData(edgeNode);

			//libera edge
			free(edge);

			//libera node da lsita
			freeNode = edgeNode;
			edgeNode = getNext(edgeNode);
			free(freeNode);
		}

		//libera list de edges e vertex
		free(edgeList);
		free(vertex);

		//libera node da list
		freeNode = vertexNode;
		vertexNode = getNext(vertexNode);
		free(freeNode);
	}

	//libera graph e vertex
	free(graph->vertexList);
	free(graph);
}
