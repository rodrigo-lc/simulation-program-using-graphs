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

#include "component.h"
#include "../linkedList/linkedList.h"
#include "../graph/graph.h"
#include "../graph/vertex.h"


struct resistors {
    edges_t* resistor;
    int voltage;
    int current;
};

struct voltageSources {
    edges_t* voltageSource;
    int voltage;
    int current;
};



