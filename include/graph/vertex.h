/*
 * vertex.h
 *
 *  Created on: Jul 5, 2016
 *      Author: Renan Augusto Starke
 */

#ifndef GRAFO_VERTICE_H_
#define GRAFO_VERTICE_H_

#include "../../include/linkedList/linkedList.h"

/* Exporta os tipos de data do vertex e edges */
typedef struct vertexes vertex_t;
typedef struct edges edges_t;

/* Tipo enum o status das edges: utilizado para exportação do DOT */
typedef enum edgeStatus { VAZIO, EXPORTADA } edgeStatus_t;

/* Cria um nodevo vertex com id */
vertex_t* createVertex(int ID);

/* Cria uma nodeva edge */
edges_t *createEdge(vertex_t* source, vertex_t* destiny, int weight);

/* Obtem id de um vertex */
int vertexGetID(vertex_t* vertex);

/* Adiciona uma edge a um graph */
void addEdge(vertex_t *vertex, edges_t *edge);

/* Obtem a list encadeada das edges */
linkedList_t* vertexGetEdges(vertex_t* vertex);

/* Retorna o weight de um edge */
int edgeGetWeight (edges_t *edge);

/* Obtem o destinho de uma edge */
vertex_t* edgeGetAdjacent(edges_t* edge);

/* Retorna uma edge caso seja fonte ou destinode */
edges_t* searchAdjacent(vertex_t* vertex, vertex_t *adjacent);

/* Configura status de uma edge */
void edgeSetStatus(edges_t *edge, edgeStatus_t status);

/* Obtem o status de uma edge */
edgeStatus_t edgeGetStatus (edges_t* edge);


/* Configura membro id_group da struct vertex
 * Ver: struct vertexs */
void vertexSetGroup(vertex_t* vertex, int group);

/* Configura membro dad da struct vertex
 * Ver: struct vertexs */
void vertexSetDad(vertex_t* vertex, vertex_t* dad);


/* Obtem membro id_group da struct vertex
int vertex_get_group(vertex_t* vertex);
 * Ver: struct vertexs


 Configura membro dist da struct vertex
 * Ver: struct vertexs
void vertex_set_dist(vertex_t *vertex, int dist);

 Obtem valor dist da struct vertex
 * Ver: struct vertexs
//int vertex_get_dist(vertex_t *vertex);

 Obtem vertex previous do menoder caminho.
 * Configurado por Dijkstra
//vertex_t *vertex_get_antec_caminho(vertex_t *vertex);

 Configura vertex antessor do menoder caminho
//void vertex_set_antec_caminho(vertex_t *vertex, vertex_t *previous);
 Retorna o comprimento de dois vertexs adjacentes
//int vertexs_comprimento(vertex_t *fonte, vertex_t *destinode);

*/

#endif /* GRAFO_VERTICE_H_ */
