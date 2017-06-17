/*
 ==============================================================================
 Name:              graph.h
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Graphs using data structures such as: linked lists, stacks and
                    queues - header file
 ==============================================================================
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "vertex.h"
#include "../stack/stack.h"

typedef struct graphs graph_t;

graph_t* createGraph(int ID);
vertex_t* graphAddVertex(graph_t* graph, int ID);

/* Cria edges:
 * graph: graph que pertence a edge
 * vertex: ponteiro do vertex que se deseja adicionar edges
 * n: numero total dos nexts parametros
 * nexts parametros: par ordenado composto por: <vert. destinode> , <weight da edge>
 * Ex: adicionar uma edge para o vertex 2 e 3 com respectivos weights 9 e 15
 * adiciona_adjacentes(graph, vertex, 4, 2, 9, 3, 15);  */
void addAdjacents(graph_t* graph, vertex_t *vertex, int n, ...);
vertex_t* searchVertex(graph_t* graph, int ID);
void exportGraphDot(const char* filename, graph_t* graph);
void freeGraph(graph_t* graph);

//stack_t* Dijkstra(graph_t* graph, vertex_t* sourceVertex, vertex_t* destinyVertex); // Minimum path
void bfs(graph_t* graph, vertex_t* initialVertex); // IMPLEMENTAR
void dfs(graph_t* graph, vertex_t* initialVertex); // IMPLEMENTAR

#endif /* GRAPH_H_ */
