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

#include "component.h"
#include "../linkedList/linkedList.h"
#include "../graph/graph.h"
#include "../graph/vertex.h"
#include "../linkedList/node.h"

enum componentType
{
    VOLTAGE_SOURCE,
    RESISTOR_PASSIVE,
    SHORT_CIRCUIT
};

struct components {
    int ID;
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

void createComponent(component_t* component, char* edgeColor, float value)
{
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

}
