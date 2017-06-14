#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED


typedef struct stacks stack_t;

stack_t* createStack(void);

void    push(void* data, stack_t *stack);
void*   pop(stack_t* stack);

int     emptyStack(stack_t* stack);
void    freeStack(stack_t* stack);

#endif // PILHA_H_INCLUDED
