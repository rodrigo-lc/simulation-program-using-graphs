#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

typedef struct nodes node_t;

node_t *createNode(void *dado);

void liga_nodes (node_t *fonte, node_t *destinode);
void desliga_node (node_t *node);

void desliga_node_previous (node_t *node);
void desliga_node_next (node_t *node);

node_t *obtem_next (node_t *node);
node_t *obtem_previous (node_t *node);
void *obter_dado (node_t *node);

#endif // NO_H_INCLUDED
