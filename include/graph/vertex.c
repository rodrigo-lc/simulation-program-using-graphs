/*
 ==============================================================================
 Name:              vertex.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Vertex structures for using in applications using graphs
 ==============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "vertex.h"
#include "../linkedList/linkedList.h"

struct vertexes {
	linkedList_t* edges;
    vertex_t* dadVertex;
    //vertex_t* previousVertex;
	int ID;
	int groupID;
    int distance;
};

struct edges {
	int weight;
	int value;
	vertex_t* sourceVertex;
	vertex_t* destinyVertex;
	edgeStatus_t status; // Status for file exportation
};

vertex_t* createVertex(int ID)
{
	vertex_t* vertex = NULL;

	vertex = malloc(sizeof(vertex_t));

	if (vertex == NULL) {
		perror("createVertex:");
		exit(EXIT_FAILURE);
	}

	vertex->ID = ID;
	vertex->edges = createLinkedList();
	vertex->groupID = -1; // -1 = Non-visited vertex
	vertex->dadVertex = NULL;

	return vertex;
}

int vertexGetID(vertex_t* vertex)
{
	if (vertex == NULL)
	{
		fprintf(stderr, "vertexGetID: Invalid vertex!\n");
		exit(EXIT_FAILURE);
	}

	return vertex->ID;
}

edges_t* createEdge(vertex_t* source, vertex_t* vertex, int weight)
{
	edges_t* edge;

	edge = (edges_t*)malloc(sizeof(edges_t));

	if (edge == NULL) {
		perror("createEdge:");
		exit(EXIT_FAILURE);
	}

	edge->weight = weight;
	edge->sourceVertex = source;
	edge->destinyVertex = vertex;

	return edge;
}

void addEdge(vertex_t* vertex, edges_t* edge)
{
	node_t* node;

	if (vertex == NULL || edge == NULL)	{
		fprintf(stderr, "addEdge: Invalid data!\n");
		exit(EXIT_FAILURE);
	}

	node = createNode(edge);
	addTail(vertex->edges, node);

}

linkedList_t* vertexGetEdges(vertex_t *vertex)
{
	if (vertex == NULL){
		fprintf(stderr, "vertexGetEdges: Invalid vertex!\n");
		exit(EXIT_FAILURE);
	}

	return vertex->edges;
}

int edgeGetWeight(edges_t* edge)
{
	if (edge == NULL)
    {
		fprintf(stderr, "edgeGetWeight: Invalid edge!\n");
		exit(EXIT_FAILURE);
	}

	return edge->weight;
}

vertex_t* edgeGetAdjacent(edges_t* edge)
{
	if (edge == NULL)
    {
		fprintf(stderr, "edgeGetAdjacent: Invalid edge!\n");
		exit(EXIT_FAILURE);
	}

	return edge->destinyVertex;
}

edges_t* searchAdjacent(vertex_t* vertex, vertex_t* adjacentVertex)
{
	node_t* node;
	edges_t* edge;

	if (vertex == NULL)
    {
		fprintf(stderr, "searchAdjacent: Invalid edge!\n");
		exit(EXIT_FAILURE);
	}

    // Edge list navegation
	node = getHead(vertex->edges);
	while (node)
    {
		edge = getData(node);

		if (edge->destinyVertex == adjacentVertex || edge->sourceVertex == adjacentVertex)
			return edge;

		node = getNext(node);
	}

	return NULL;
}

edgeStatus_t edgeGetStatus(edges_t* edge)
{
	if (edge == NULL){
		fprintf(stderr, "edgeGetStatus: Invalid edge!\n");
		exit(EXIT_FAILURE);
	}

	return edge->status;
}

void edgeSetStatus(edges_t* edge, edgeStatus_t status)
{
	if (edge == NULL)
    {
		fprintf(stderr, "edgeSetStatus: Invalid edge!\n");
		exit(EXIT_FAILURE);
	}

	edge->status = status;
}

/*------------------------------------------*/
void vertexSetGroup(vertex_t* vertex, int group)
{
	if (vertex == NULL)
    {
			fprintf(stderr, "vertexSetGroup: Invalid vertex!\n");
			exit(EXIT_FAILURE);
	}

	vertex->groupID = group;
}

int vertexGetGroup(vertex_t* vertex)
{
	if (vertex == NULL)
    {
			fprintf(stderr, "vertexGetGroup: Invalid vertex\n");
			exit(EXIT_FAILURE);
	}

	return vertex->groupID;
}

void vertexSetDad(vertex_t* vertex, vertex_t* dadVertex)
{
	if (vertex == NULL)
    {
			fprintf(stderr, "vertexSetDad: Invalid vertex!\n");
			exit(EXIT_FAILURE);
	}

	vertex->dadVertex = dadVertex;
}

void printVertex(vertex_t* vertex)
{
    if (vertex == NULL)
    {
			fprintf(stderr, "printVertex: Invalid vertex!\n");
			exit(EXIT_FAILURE);
	}
	printf("Pointer: %p\nID: %d\n", vertex, vertex->ID);
}

//void vertexSetDistance(vertex_t* vertex, int distance) {
//
//	if (vertex == NULL)
//    {
//			fprintf(stderr, "vertexSetDistance: Invalid vertex!\n");
//			exit(EXIT_FAILURE);
//	}
//
//	vertex->distance = distance;
//}
//
//int vertexGetDistance(vertex_t* vertex){
//
//	if (vertex == NULL)
//  {
//			fprintf(stderr, "vertexGetDistance: Invalid vertex!\n");
//			exit(EXIT_FAILURE);
//	}
//
//	return vertex->distance;
//}
//
//int vertexGetLenght(vertex_t* sourceVertex, vertex_t* destinyVertex)
//{
//	edges_t* edge;
//
//	if (sourceVertex == NULL || destinyVertex == NULL)
//    {
//		fprintf(stderr, "vertexGetLenght: Invalid vertexes!\n");
//		exit(EXIT_FAILURE);
//	}
//
//	edge = searchAdjacent(sourceVertex, destinyVertex);
//
//	if (edge == NULL)
//    {
//		fprintf(stderr, "vertexGetLenght: Non-adjacent vertexes!\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return edge->weight;
//}
//
//void vertexSetPrevious(vertex_t* vertex, vertex_t* previousVertex)
//{
//	if (vertex == NULL || previousVertex == NULL)
//    {
//		fprintf(stderr, "vertexSetPrevious: Invalid vertexes!\n");
//		exit(EXIT_FAILURE);
//	}
//
//	vertex->previousVertex = previousVertex;
//}
//
//vertex_t* vertexGetPrevious(vertex_t* vertex)
//{
//	if (vertex == NULL)
//    {
//		fprintf(stderr, "vertexGetPrevious: Invalid vertex\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return vertex->previousVertex;
//}
