#ifndef NO_H_INCLUDED
#define NO_H_INCLUDED

typedef struct nodes node_t;

node_t* createNode(void *data);

void connectNodes(node_t* sourceNode, node_t* destinyNode);
void disconnectNode(node_t* node);
void disconnectPreviousNode(node_t* node);
void disconnectNextNode(node_t* node);

node_t* getNext(node_t* node);
node_t* getPrevious(node_t* node);
void* getData(node_t* node);

#endif // NO_H_INCLUDED
