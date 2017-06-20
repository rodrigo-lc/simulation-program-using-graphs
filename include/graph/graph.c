/*
 ==============================================================================
 Name:              graph.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 20/06/2017
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
#include "../component/component.h"

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
		return NULL;

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

// Breadth First Search
void bfs(graph_t* graph, vertex_t* initialVertex)
{
    if (graph == NULL)
    {
		perror("bfs: Invalid graph pointer!");
		exit(EXIT_FAILURE);
	}

    queue_t* queue = createQueue();
    vertex_t* vertex = NULL;

    node_t* node = getHead(graph->vertexList);
    while(node)
    {
        vertex = getData(node);
        vertexSetGroup(vertex, INFINITE);
        vertexSetDad(vertex, NULL);

        node = getNext(node);
    }

    node = getHead(graph->vertexList);

    vertex = initialVertex;
    vertexSetGroup(vertex, 0);

    enqueue(vertex, queue);
    while(!isQueueEmpty(queue))
    {
        vertex = dequeue(queue);

        linkedList_t* neighborList = vertexGetEdges(vertex);
        node_t* neighborNode = getHead(neighborList);
        while(neighborNode)
        {
            vertex_t* neighborVertex = edgeGetAdjacent(getData(neighborNode));
            int distance = vertexGetGroup(neighborVertex);
            if(distance == INFINITE)
            {
                vertexSetGroup(neighborVertex, vertexGetGroup(vertex)+1);
                vertexSetDad(neighborVertex, vertex);
                enqueue(neighborVertex, queue);
            }
            neighborNode = getNext(neighborNode);
        }
    }


}

// Depth First Search
void dfs(graph_t* graph, vertex_t* initialVertex)
{
    if (graph == NULL)
    {
		perror("dfs: Invalid graph pointer!");
		exit(EXIT_FAILURE);
	}

    stack_t* stack = createStack();
    vertex_t* vertex = NULL;

    // Vertex list navegation
    node_t* node = getHead(graph->vertexList);
    while(node)
    {
        vertex = getData(node);
        vertexSetGroup(vertex, 0); // Set visited by group = 0
        vertexSetDad(vertex, NULL);
        node = getNext(node);
    }

    vertex = initialVertex;
    push(vertex, stack);

    while(!isStackEmpty(stack))
    {
        vertex = pop(stack);

        if(!vertexGetGroup(vertex)){
            vertexSetGroup(vertex, 1);

            linkedList_t* neighborList = vertexGetEdges(vertex);

            // Navigation in neighborNode list
            node_t* neighborNode = getHead(neighborList);
            while(neighborNode)
            {
                vertex_t* neighborVertex = edgeGetAdjacent(getData(neighborNode));
                push(neighborVertex, stack);
                vertexSetDad(neighborVertex, vertex);
                neighborNode = getNext(neighborNode);
            }
        }
    }
}

linkedList_t* loopSearch(graph_t* graph, vertex_t* initialVertex)
{
    if (graph == NULL)
    {
		perror("loopSearch: Invalid graph pointer!");
		exit(EXIT_FAILURE);
	}

    stack_t* stack = createStack();
    vertex_t* vertex = NULL;
    linkedList_t* visitedList = createLinkedList();
    linkedList_t* loopsList = createLinkedList();
    edges_t* edge = NULL;
    edges_t* initialEdge = NULL;

    // Vertex list navegation
    node_t* node = getHead(graph->vertexList);
    while(node)
    {
        vertex = getData(node);
        vertexSetGroup(vertex, 0); // Set visited by group = 0
        vertexSetDad(vertex, NULL);
        node = getNext(node);
    }

    vertex = initialVertex;
    initialEdge = createEdge(vertex, vertex, 0);     //need to free later
    push(initialEdge, stack);

    while(!isStackEmpty(stack))
    {
        edge = pop(stack);
        vertex = edgeGetAdjacent(edge);

        if(!vertexGetGroup(vertex))
        {
            vertexSetGroup(vertex, 1);

            node = createNode(edge);
            addTail(visitedList, node);

            linkedList_t* neighborList = vertexGetEdges(vertex);

            // Navigation in neighborNode list
            node_t* neighborNode = getHead(neighborList);
            while(neighborNode)
            {
                edge = getData(neighborNode);
                vertex_t* neighborVertex = edgeGetAdjacent(edge);
                if(neighborVertex != vertexGetDad(vertex))
                    push(edge, stack);
                vertexSetDad(neighborVertex, vertex);
                neighborNode = getNext(neighborNode);
            }
        }
        else if(!isEdgeUsed(edge) && !isEdgeUsed(counterEdge(edge)))
        {
            createLoop(loopsList, visitedList, edge);
            setUsedEdge(edge, 1);
            setUsedEdge(counterEdge(edge), 1);
        }
    }

    return loopsList;
}

linkedList_t* buildGraph(graph_t* graph, char* filename)
{
    char buffer[BUFFER_SIZE];
	char componentName[BUFFER_SIZE];
	float value = 0; // resistance or voltage
	int returnValue = 0; // return value for sscanf
	int sourceID, destinyID;
	vertex_t* sourceVertex;
	vertex_t* destinyVertex;

    linkedList_t* vertexList;
    FILE* file;

	file = fopen(filename, "r");

	if (file == NULL)
    {
		perror("buildGraph: Invalid file pointer!");
		exit(EXIT_FAILURE);
	}

	vertexList = createLinkedList();
    graph->vertexList = vertexList;

	fgets(buffer, BUFFER_SIZE, file);

    while(fgets(buffer, BUFFER_SIZE, file) != 0)
    {
        if(buffer[0] == '}')
            break;

		returnValue = sscanf(buffer, "%i--%i [color=%[^,], label=%f];\n", &sourceID, &destinyID, componentName, &value);

        printf("\nreturn: %i\nsource: %i\ndestiny: %i\ncomponentname: %s\nvalue: %.2f\n", returnValue,  sourceID, destinyID, componentName, value);

        if (returnValue != 4)
        {
			fprintf(stderr, "Invalid file!\n");
			exit(EXIT_FAILURE);
		}

        sourceVertex = searchVertex(graph, sourceID);
        if(sourceVertex == NULL)                            //if new vertex, add to vertexList
        {
            sourceVertex = createVertex(sourceID);
            node_t* node = createNode(sourceVertex);
            addTail(vertexList, node);
        }

        destinyVertex = searchVertex(graph, destinyID);
        if(destinyVertex == NULL)
        {
            destinyVertex = createVertex(destinyID);
            node_t* node = createNode(destinyVertex);
            addTail(vertexList, node);
        }

        component_t* component = createComponent(componentName, value);
        edges_t* edge = createEdge(sourceVertex, destinyVertex, component);
        addEdge(sourceVertex, edge);

        component = createComponent(componentName, -value);
        edge = createEdge(destinyVertex, sourceVertex, component);
        addEdge(destinyVertex, edge);
    }

    // add ADJACENTS



    //
	/* Fecha arquivo */
	fclose(file);

	return vertexList;
}



//--------------------------------------------------------------------------------------
