/*
 ==============================================================================
 Name:              vertex.c
 Contributors:      Renan Augusto Starke, Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        05/07/2016
 Version:           1.0
 Last modification: 24/05/2017
 Copyright:         MIT License
 Description:       Vertex structures for using in applications using graphs
 ==============================================================================
 */

#include <stdlib.h>
#include <stdio.h>

#include "vertex.h"
#include "../linkedList/linkedList.h"

struct vertexes
{
	int ID;
	linkedList_t* edges;

	/* Informacoes para componentes conexos */
	int groupID;
	vertex_t* dad;

};

struct edges {
	int weight;
	vertex_t* sourceVertex;
	vertex_t* destinyVertex;

	/* status para expotacao em arquivo */
	edgeStatus_t status;
};


vertex_t* createVertex(int ID)
{
	vertex_t* vertex = NULL;

	vertex = malloc(sizeof(vertex_t));

	if (vertex == NULL) {
		perror("create_vertex:");
		exit(EXIT_FAILURE);
	}

	vertex->ID = ID;
	vertex->edges = createLinkedList();
	vertex->groupID = -1;
	vertex->dad = NULL;

	return vertex;
}

int vertexGetID(vertex_t* vertex)
{
	if (vertex == NULL)
	{
		fprintf(stderr, "vertex_obter_id: vertex invalido!\n");
		exit(EXIT_FAILURE);
	}

	return vertex->ID;
}

edges_t* createEdge(vertex_t* source, vertex_t* vertex, int weight)
{
	edges_t* edge;

	edge = (edges_t*)malloc(sizeof(edges_t));

	if (edge == NULL) {
		perror("create_edge:");
		exit(EXIT_FAILURE);
	}

	edge->weight = weight;
	edge->sourceVertex = source;
	edge->destinyVertex = vertex;

	return edge;
}

void adiciona_edge(vertex_t *vertex, edges_t *edge)
{
	node_t *node;

	if (vertex == NULL || edge == NULL)	{
		fprintf(stderr, "adiciona_edge: data invalidos\n");
		exit(EXIT_FAILURE);
	}

	node = create_node(edge);
	add_tail(vertex->edges, node);

}

linkedList_t *vertex_get_edges(vertex_t *vertex)
{
	if (vertex == NULL){
		fprintf(stderr, "vertex_get_edges: vertex invalido\n");
		exit(EXIT_FAILURE);
	}

	return vertex->edges;
}

int edge_get_weight (edges_t *edge) {
	if (edge == NULL){
		fprintf(stderr, "edge_get_weight: edge invalido\n");
		exit(EXIT_FAILURE);
	}

	return edge->weight;
}

vertex_t* edgeGetAdjacent(edges_t* edge)
{
	if (edge == NULL){
		fprintf(stderr, "edge_get_adjacente: edge invalido\n");
		exit(EXIT_FAILURE);
	}

	return edge->destinyVertex;
}

edges_t *procurar_adjacente(vertex_t* vertex, vertex_t* adjacentVertex)
{
	node_t* node;
	edges_t* edge;

	if (vertex == NULL){
		fprintf(stderr, "procurar_adjacente: edge invalido\n");
		exit(EXIT_FAILURE);
	}

	node = getHead(vertex->edges);

	while (node){

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
		fprintf(stderr, "edge_get_status: edge invalida\n");
		exit(EXIT_FAILURE);
	}

	return edge->status;
}

void edgeSetStatus(edges_t* edge, edgeStatus_t status)
{
	if (edge == NULL){
		fprintf(stderr, "edge_set_status: edge invalida\n");
		exit(EXIT_FAILURE);
	}

	edge->status = status;
}

/*------------------------------------------*/
void vertexSetGroup(vertex_t* vertex, int group) {

	if (vertex == NULL){
			fprintf(stderr, "vertex_set_group: vertex invalido\n");
			exit(EXIT_FAILURE);
	}

	vertex->groupID = group;
}

int vertexGetGroup(vertex_t* vertex) {

	if (vertex == NULL){
			fprintf(stderr, "vertex_get_group: vertex invalido\n");
			exit(EXIT_FAILURE);
	}

	return vertex->groupID;
}

void vertexSetDad(vertex_t* vertex, vertex_t* dad) {

	if (vertex == NULL){
			fprintf(stderr, "vertex_set_dad: vertex invalido\n");
			exit(EXIT_FAILURE);
	}

	vertex->dad = dad;
}






//void vertex_set_dist(vertex_t *vertex, int dist) {
//
//	if (vertex == NULL){
//			fprintf(stderr, "vertex_set_dist: vertex invalido\n");
//			exit(EXIT_FAILURE);
//	}
//
//	vertex->dist =  dist;
//}
//
//int vertex_get_dist(vertex_t *vertex){
//
//	if (vertex == NULL){
//			fprintf(stderr, "vertex_get_dist: vertex invalido\n");
//			exit(EXIT_FAILURE);
//	}
//
//	return vertex->dist;
//}
//
//int vertexs_comprimento(vertex_t *fonte, vertex_t *destinode)
//{
//	edges_t *edge;
//
//	if (fonte == NULL || destinode == NULL){
//		fprintf(stderr, "vertexs_comprimento: vertexs invalidos\n");
//		exit(EXIT_FAILURE);
//	}
//
//	edge = procurar_adjacente(fonte, destinode);
//
//	if (edge == NULL) {
//		fprintf(stderr, "vertexs_comprimento: vertexs nao adjacentes\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return edge->weight;
//}
//
//void vertex_set_antec_caminho(vertex_t *vertex, vertex_t *antecessor){
//
//	if (vertex == NULL || antecessor == NULL){
//		fprintf(stderr, "vertex_set_antec_caminho: vertexs invalidos\n");
//		exit(EXIT_FAILURE);
//	}
//
//	vertex->antecessor_caminho = antecessor;
//}
//
//vertex_t *vertex_get_antec_caminho(vertex_t *vertex) {
//	if (vertex == NULL){
//		fprintf(stderr, "vertex_get_antec_aminho: vertex invalidos\n");
//		exit(EXIT_FAILURE);
//	}
//
//	return vertex->antecessor_caminho;
//}
