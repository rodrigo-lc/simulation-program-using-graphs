/*
 ==============================================================================
 Name:              vertex.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Vertex structures for using in applications using graphs -
                    header file
 ==============================================================================
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include "../../include/linkedList/linkedList.h"

typedef struct vertexes vertex_t;
typedef struct edges edges_t;
typedef enum edgeStatus {EMPTY, EXPORTED} edgeStatus_t; // type for exportation in .dot file

vertex_t* createVertex(int ID);
void vertexSetGroup(vertex_t* vertex, int group);
void vertexSetDad(vertex_t* vertex, vertex_t* dadVertex);
void printVertex(vertex_t* vertex);
int vertexGetID(vertex_t* vertex);
int vertexGetGroup(vertex_t* vertex);
linkedList_t* vertexGetEdges(vertex_t* vertex);
vertex_t* edgeGetAdjacent(edges_t* edge);
vertex_t* edgeGetSource(edges_t* edge);
vertex_t* vertexGetDad(vertex_t* vertex);
edges_t* createEdge(vertex_t* sourceVertex, vertex_t* destinyVertex, int weight);
void addEdge(vertex_t *vertex, edges_t* edge);
int edgeGetWeight (edges_t* edge);
edges_t* searchAdjacent(vertex_t* vertex, vertex_t* adjacentVertex);
void edgeSetStatus(edges_t* edge, edgeStatus_t status);
edgeStatus_t edgeGetStatus (edges_t* edge);
void vertexSetVisited(vertex_t *vertex, int x);
int vertexGetVisited(vertex_t* vertex);
void printNeighborsList(vertex_t* vertex);
void createLoop(linkedList_t* loopsList, linkedList_t* visitedList, edges_t* edge);
int isEdgeUsed(edges_t* edge);
void setUsedEdge(edges_t* edge, int i);
edges_t* counterEdge(edges_t* edge);

//void vertexSetDistance(vertex_t *vertex, int distance);
//int vertexGetDistance(vertex_t* vertex);
//vertex_t* vertexGetPrevious(vertex_t* vertex);
//void vertexSetPrevious(vertex_t* vertex, vertex_t* previousVertex);
//int vertexGetLenght(vertex_t* sourceVertex, vertex_t* destinyVertex);

#endif /* VERTEX_H_ */
