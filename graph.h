/*
 * graph.h
 *
 *  Created on: Jul 5, 2016
 *      Author: Renan Augusto Starke
 */

#ifndef GRAFO_GRAFO_H_
#define GRAFO_GRAFO_H_

#include "vertex.h"
#include "../stack/stack.h"

typedef struct graphs graph_t;

/* Cria um nodevo graph com id */
graph_t *createGraph(int ID);

/* Adiciona um vertex ao graph */
vertex_t* graphAddVertex(graph_t* graph, int ID);

/* Cria edges:
 * graph: graph que pertence a edge
 * vertex: ponteiro do vertex que se deseja adicionar edges
 * n: numero total dos nexts parametros
 * nexts parametros: par ordenado composto por: <vert. destinode> , <weight da edge>
 * Ex: adicionar uma edge para o vertex 2 e 3 com respectivos weights 9 e 15
 * adiciona_adjacentes(graph, vertex, 4, 2, 9, 3, 15);  */
void addAdjacents(graph_t* graph, vertex_t *vertex, int n, ...);

/* Procura um vertex node graph com id numerico */
vertex_t* searchVertex(graph_t* graph, int ID);

/* Exporta o graph utilizando a linguagem dot */
void exportGraphDot(const char* filename, graph_t* graph);

/* Libera memoria utilizada pelo graph */
void freeGraph(graph_t* graph);

/* Menoder camingo entre todos os nodes:
 * retorna um pilha do caminho entre fonte e destinode  */
stack_t* Dijkstra(graph_t *graph, vertex_t* fonte, vertex_t* destinode);

/* Procura um vertex com menoder a menoder distancia
 * Ver: struct vertexs */
node_t* searchCloserVertex(linkedList_t *Q); // IMPLEMENTAR

void bfs(graph_t* graph, vertex_t* initialVertex); // IMPLEMENTAR

void dfs(graph_t* graph, vertex_t* initialVertex); // IMPLEMENTAR

#endif /* GRAFO_GRAFO_H_ */
