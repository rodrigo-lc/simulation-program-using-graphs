/*
 ==============================================================================
 Name:              graph.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
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
//#define DEBUG
#define FALSE       0
#define TRUE        1
#define INFINITE    INT_MAX


struct graphs {
	int ID;
	linkedList_t* vertexList;
};

//--------------------------------------------------------------------------------------

void bfs(graph_t *graph, vertex_t* inicial)
{
    if (grafo == NULL) {
		perror("bfs: grafo invalido");
		exit(EXIT_FAILURE);
	}

    fila_t *fila = cria_fila();
    vertice_t *vertice = NULL;

    no_t *no = obter_cabeca(grafo->vertices);
    while(no)
    {
        vertice = obter_dado(no);
        vertice_set_dist(vertice, INFINITO);
        vertice_set_pai(vertice, NULL);

        no = obtem_proximo(no);
    }

    no = obter_cabeca(grafo->vertices);


    vertice = inicial;
    vertice_set_dist(vertice, 0);

    enqueue(vertice, fila);
    while(!fila_vazia(fila))
    {
        vertice = dequeue(fila);

        lista_enc_t *vizinhos = vertice_get_arestas(vertice);
        no_t *no_vizinho = obter_cabeca(vizinhos);
        while(no_vizinho)
        {
            vertice_t *vizinho = aresta_get_adjacente(obter_dado(no_vizinho));
            int dist = vertice_get_dist(vizinho);
            if(dist == INFINITO)
            {
                vertice_set_dist(vizinho,vertice_get_dist(vertice)+1);
                vertice_set_pai(vizinho, vertice);
                enqueue(vizinho, fila);
            }
            no_vizinho = obtem_proximo(no_vizinho);
        }
    }


}


void dfs(grafo_t *grafo, vertice_t* inicial)
{
    if (grafo == NULL) {
		perror("dfs: grafo invalido");
		exit(EXIT_FAILURE);
	}

    pilha_t *pilha = cria_pilha();
    vertice_t *vertice = NULL;

    no_t *no = obter_cabeca(grafo->vertices);
    while(no)
    {
        vertice = obter_dado(no);
        vertice_set_visitado(vertice, 0);
        vertice_set_pai(vertice, NULL);
        no = obtem_proximo(no);
    }

    vertice = inicial;
    push(vertice, pilha);
    while(!pilha_vazia(pilha))
    {
        vertice = pop(pilha);

        if(!vertice_get_visitado(vertice)){
            vertice_set_visitado(vertice, 1);

            lista_enc_t *vizinhos = vertice_get_arestas(vertice);
            no_t *no_vizinho = obter_cabeca(vizinhos);
            while(no_vizinho)
            {
                vertice_t *vizinho = aresta_get_adjacente(obter_dado(no_vizinho));
                push(vizinho, pilha);
                vertice_set_pai(vizinho, vertice);
                no_vizinho = obtem_proximo(no_vizinho);
            }
        }
    }
}

//--------------------------------------------------------------------------------------

graph_t* createGraph(int ID)
{
	graph_t* graph = NULL;

	graph = (graph_t*) malloc(sizeof(graph_t));

	if (graph == NULL)
    {
		perror("createGraph:");
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
	printf("graphAddVertex: %d\n", ID);
#endif

	if (graph == NULL)
    {
        fprintf(stderr,"graphAddVertex: Invalid graph!");
        exit(EXIT_FAILURE);
	}

	if (searchVertex(graph, ID) != NULL)
    {
		fprintf(stderr,"graphAddVertex: Duplicated vertexes!\n");
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
		fprintf(stderr, "searchVertex: Invalid graph!");
		exit(EXIT_FAILURE);
	}

	if (isListEmpty(graph->vertexList) == TRUE)
		return FALSE;

	nodeList = getHead(graph->vertexList);

	while (nodeList)
	{
		// Get list address
		vertex = getData(nodeList);

		// Get ID
		myID = vertexGetID(vertex);

		if (myID == ID)
        {
			return vertex;
		}

		nodeList = getNext(nodeList);
	}
	return NULL;
}

void addAdjacents(graph_t* graph, vertex_t* vertex, int n, ...)
{
	va_list arguments;
	vertex_t* nextVertex;
	edges_t* edge;

	int nextID;
	int weight;
    int i;

	// Initializing arguments to store all values after num
	va_start (arguments, n);

	for (i = 0; i < n; (i = (i + 2)))
	{
		nextID = va_arg(arguments, int);
		weight = va_arg(arguments, int);

		nextVertex = searchVertex(graph, nextID);

		if (nextVertex == NULL)
        {
			fprintf(stderr, "addAdjacents: Cannot find next vertex in graph\n");
			exit(EXIT_FAILURE);
		}

		edge = createEdge(vertex, nextVertex, weight);
		addEdge(vertex, edge);

#ifdef DEBUG
		printf("\tVertexID: %d\n", vertexGetID(vertex));
		printf("\tNext: %d\n", nextID);
		printf("\tWeight: %d\n", weight);
#endif

	} // end for

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

	if (filename == NULL || graph == NULL)
    {
		fprintf(stderr, "exportGraphDot: Invalid pointers!\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(filename, "w");

	if (file == NULL){
		perror("exportGraphDot:");
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
		while (edgeNode)
        {
			edge = getData(edgeNode);

			//ignodera caso já exportada
			if (edgeGetStatus(edge) == EXPORTED)
            {
				edgeNode = getNext(edgeNode);
				continue;
			}

			//marca como exportada esta edge
			edgeSetStatus(edge, EXPORTED);
			adjacentVertex = edgeGetAdjacent(edge);

			//marca contra-edge também como exporta node caso de graph não direcionados
			counterEdge = searchAdjacent(adjacentVertex, vertex);
			edgeSetStatus(counterEdge, EXPORTED);

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

	if (graph == NULL)
    {
		fprintf(stderr, "freeGraph: Invalid graph!\n");
		exit(EXIT_FAILURE);
	}

	// Navegation in list of vertexes
	vertexNode = getHead(graph->vertexList);
	while (vertexNode)
    {
		vertex = getData(vertexNode);

		// Free every edge
		edgeList = vertexGetEdges(vertex);
		edgeNode = getHead(edgeList);
		while (edgeNode)
        {
			edge = getData(edgeNode);

			// Free edge
			free(edge);

			// Free list node
			freeNode = edgeNode;
			edgeNode = getNext(edgeNode);
			free(freeNode);
		}

		// Free edge list and vertex
		free(edgeList);
		free(vertex);

		// Free list node
		freeNode = vertexNode;
		vertexNode = getNext(vertexNode);
		free(freeNode);
	}

	// Free vertex list and graph
	free(graph->vertexList);
	free(graph);
}
