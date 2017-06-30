/*
 ==============================================================================
 Name:              component.c
 Contributors:      Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        16/06/2017
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Electric components structures for using in applications using graphs
 ==============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <conio.h>

#include "component.h"
#include "../linkedList/linkedList.h"
#include "../graph/graph.h"
#include "../graph/vertex.h"
#include "../linkedList/node.h"
#include "../graph/vertex.h"

//#define DEBUG

enum componentType
{
    VOLTAGE_SOURCE,
    RESISTOR_PASSIVE,
    SHORT_CIRCUIT
};

struct components {
    int ID[2];
    int type;
    float value;
    float current;
    int* vector;
};

float componentGetValue(component_t* component)
{
    if (component == NULL)
    {
		perror("componentGetValue: Invalid pointer!");
		exit(EXIT_FAILURE);
	}
    return component->value;
}

int componentGetType(component_t* component)
{
    if (component == NULL)
    {
		perror("componentGetType: Invalid pointer!");
		exit(EXIT_FAILURE);
	}
    return component->type;
}

float componentGetCurrent(component_t* component)
{
    if (component == NULL)
    {
		perror("componentGetType: Invalid pointer!");
		exit(EXIT_FAILURE);
	}
    return component->current;
}

float componentGetVoltage(component_t* component)
{
    if (component == NULL)
    {
		perror("componentGetType: createComponent: Invalid pointer!");
		exit(EXIT_FAILURE);
	}
    if(component->type == VOLTAGE_SOURCE)
        return component->value;
    if(component->type == RESISTOR_PASSIVE)
        return (component->current)*(component->value);
    if(component->type == SHORT_CIRCUIT)
        return 0;
    return 0; // avoiding warnings
}

component_t* createComponent(char* edgeColor, float value, int ID1, int ID2)
{
    component_t* component = malloc(sizeof(component_t));

    if (component == NULL)
    {
		perror("createComponent: Invalid pointer!");
		exit(EXIT_FAILURE);
	}

    if(!strcmp("red", edgeColor))
    {
        component->type = RESISTOR_PASSIVE;
    }
    if(!strcmp("blue", edgeColor))
    {
        component->type = VOLTAGE_SOURCE;
    }
    if(!strcmp("black", edgeColor))
    {
        component->type = SHORT_CIRCUIT;
    }
    component->value = value;
    component->current = 0;
    component->vector = NULL;
    component->ID[0] = ID1;
    component->ID[1] = ID2;

    return component;
}

void calculateCircuit(linkedList_t* loopsList, linkedList_t* componentsList)
{
    int size = listGetSize(loopsList);
    int i = 0, n = 0;

    node_t* loopsNode = getHead(loopsList);
    linkedList_t* loopList = getData(loopsNode);
    node_t* node = NULL;
    edges_t* edge = NULL;
    component_t* component = NULL;

    while(loopsNode)                                    //set current vector on components
    {
        loopList = getData(loopsNode);
        node = getHead(loopList);
        while(node)
        {
            edge = getData(node);
            component = edgeGetData(edge);

            if(component->vector == NULL)
            {
                component->vector = malloc(size*sizeof(int));
                for(n=0; n<=size-1; n++)
                {
                    component->vector[n] = 0;
                }
            }
            component->vector[i] = 1;
            node = getNext(node);
        }
        i++;
        loopsNode = getNext(loopsNode);
    }

//------------------------------- Build Matrix -------------------------------//

    float matrix[size][size+1];
    for(i=0; i<size; i++)
    {
        for(n=0; n<=size; n++)
        {
            matrix[i][n] = 0;
        }
    }

    i = 0;
    loopsNode = getHead(loopsList);
    while(loopsNode)
    {

        loopList = getData(loopsNode);
        node = getHead(loopList);
        while(node)
        {
            edge = getData(node);
            component = edgeGetData(edge);

            if(component->type == VOLTAGE_SOURCE)
            {
                matrix[i][size] += component->value;
            }
            else if(component->type == RESISTOR_PASSIVE)
            {
                for(n=0; n<size; n++)
                {
                    matrix[i][n] += (component->vector[n])*component->value;
                }
            }
            node = getNext(node);
        }
        i++;
        loopsNode = getNext(loopsNode);
    }

    printf("\nThe resulting matrix is: \n");
    for(i=1; i<=size; i++)
    {
        printf(" I%d\t", i);
    }
    printf(" V\n");
    for(i=0; i<size; i++)               //print matrix
    {
        for(n=0; n<=size; n++)
        {
            printf("%.2f\t", matrix[i][n]);
        }
        printf("\n");
    }
    printf("\n");
//------------------------------- Solve Matrix -------------------------------//

    int d, j;
    float temp;

    for(d=0; d<size; d++)               // d = diagonal
    {
        temp = matrix[d][d];
        if(temp == 0)                   // if diagonal == 0, swap lines
        {
            for(i=d; matrix[i][d]!=0; i++);
            for(j=d; j<=size; j++)
            {
                temp = matrix[d][j];
                matrix[d][j] = matrix[i][j];
                matrix[i][j] = temp;
            }
        }

        temp = matrix[d][d];
        for(j=d; j<=size; j++)          // line(d) /= matrix[d][d]
        {
            matrix[d][j] /= temp;
        }

        for(i=d+1; i<size; i++)
        {
            temp = matrix[i][d];
            for(j=d; j<=size; j++)
            {
                matrix[i][j] = ((matrix[i][j]/temp) - matrix[d][j]);
            }
        }
    }

    for(d=size-1; d>=0; d--)
    {
        for(i=d-1; i>=0; i--)
        {
            temp = matrix[i][d];
            for(j=d; j<=size; j++)
            {
                matrix[i][j] -= (matrix[d][j]*temp);
            }
        }
    }


//----------------------------------------------------------------------------//


    for(i=1; i<=size; i++)
    {
        printf(" I%d\t", i);
    }
    printf(" V\n");
    for(i=0; i<size; i++)               //print matrix
    {
        for(n=0; n<=size; n++)
        {
            printf("%.2f\t", matrix[i][n]);
        }
        printf("\n");
    }

//    node = getHead(componentsList);
//    while(node)
//    {
//        component_t* component = getData(node);
//        if(component->type == 0)
//        for(i=0; i<size; i++)
//        {
//            component->current = matrix[i][size]*component->vector[i];
//        }
//        node = getNext(node);
//    }

}

void printResults(linkedList_t* componentsList) //fazer teste de ponteiro
{
    node_t* node = getHead(componentsList);
    printf("\nResults:");

    while(node)
    {
        component_t* component = getData(node);
        printf("V(%d-%d) = %d", component->ID[0], component->ID[1], componentGetVoltage(component));
        printf("I(%d-%d) = %d", component->ID[0], component->ID[1], component->current);

        node = getNext(node);
    }


}
