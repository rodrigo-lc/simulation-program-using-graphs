/*
 ==============================================================================
 Name:              component.h
 Contributors:      Caio Felipe Campoy, Rodrigo Luiz da Costa
 Created on:        16/06/2017
 Version:           1.0
 Last modification: 16/06/2017
 Copyright:         MIT License
 Description:       Electric components structures for using in applications using graphs
                    - header file
 ==============================================================================
 */

#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED
#include "../linkedList/linkedList.h"

typedef struct components component_t;
typedef struct resistors resistor_t;
typedef struct voltageSources voltageSource_t;

float componentGetValue(component_t* component);
void componentSetValue(component_t* component, float value);
float componentGetCurrent(component_t* component);
int componentGetType(component_t* component);
float componentGetVoltage(component_t* component);
component_t* createComponent(char* edgeColor, float value, int ID1, int ID2);
void calculateCircuit(linkedList_t* loopsList, linkedList_t* componentsList);

#endif // COMPONENT_H_INCLUDED
