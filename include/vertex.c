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
	int id;
	linkedList_t* edges;

	/* Informacoes para componentes conexos */
	int id_group;
	vertex_t* dad;

};

struct edges {
	int weight;
	vertex_t *fonte;
	vertex_t *dest;

	/* status para expotacao em arquivo */
	status_edge_t status;
};


vertex_t* createVertex(int id)
{
	vertex_t *p = NULL;

	p = malloc(sizeof(vertex_t));

	if (p == NULL) {
		perror("create_vertex:");
		exit(EXIT_FAILURE);
	}

	p->id = id;
	p->edges = createLinkedList();
	p->id_group = -1;
	p->dad = NULL;

	return p;
}

int vertex_get_id(vertex_t *vertex)
{
	if (vertex == NULL)
	{
		fprintf(stderr, "vertex_obter_id: vertex invalido!\n");
		exit(EXIT_FAILURE);
	}

	return vertex->id;
}

edges_t *create_edge(vertex_t *fonte, vertex_t *destinode, int weight)
{
	edges_t *p;

	p = (edges_t*)malloc(sizeof(edges_t));

	if (p == NULL) {
		perror("create_edge:");
		exit(EXIT_FAILURE);
	}

	p->weight = weight;
	p->fonte = fonte;
	p->dest = destinode;

	return p;
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

vertex_t *edge_get_adjacente(edges_t *edge)
{
	if (edge == NULL){
		fprintf(stderr, "edge_get_adjacente: edge invalido\n");
		exit(EXIT_FAILURE);
	}

	return edge->dest;
}

edges_t *procurar_adjacente(vertex_t *vertex, vertex_t *adjacente)
{
	node_t *node;
	edges_t *edge;

	if (vertex == NULL){
		fprintf(stderr, "procurar_adjacente: edge invalido\n");
		exit(EXIT_FAILURE);
	}

	node = obter_cabeca(vertex->edges);

	while (node){

		edge = obter_dado(node);

		if (edge->dest == adjacente || edge->fonte == adjacente)
			return edge;

		node = obtem_next(node);
	}

	return NULL;
}

status_edge_t edge_get_status (edges_t *edge)
{
	if (edge == NULL){
		fprintf(stderr, "edge_get_status: edge invalida\n");
		exit(EXIT_FAILURE);
	}

	return edge->status;
}

void edge_set_status(edges_t *edge, status_edge_t status)
{
	if (edge == NULL){
		fprintf(stderr, "edge_set_status: edge invalida\n");
		exit(EXIT_FAILURE);
	}

	edge->status = status;
}

/*------------------------------------------*/
void vertex_set_group(vertex_t *vertex, int group) {

	if (vertex == NULL){
			fprintf(stderr, "vertex_set_group: vertex invalido\n");
			exit(EXIT_FAILURE);
	}

	vertex->id_group = group;
}

int vertex_get_group(vertex_t *vertex) {

	if (vertex == NULL){
			fprintf(stderr, "vertex_get_group: vertex invalido\n");
			exit(EXIT_FAILURE);
	}

	return vertex->id_group;
}

void vertex_set_dad(vertex_t *vertex, vertex_t *dad) {

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
