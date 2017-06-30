# simulation-program-using-graphs
A basic electric circuit simulation program using graphs to apply Kirchhoff's network laws and compute voltage and current parameters.

## user interface
The user must enter a graph following a text pattern in a .dot file. \n
The file must be named "graph.dot" \n
In the first line the user need to write "graph {", optional information as node shapes and orientation must be in this same line, after the "{".
Afterwards, the user must write the conections, line by line, ending the line with a semicolon. Each vertex (source and destiny) must have an integer as ID, and be separed by two hyphens.
Aiming to differentiate the components, the user must follow this pattern:
RESISTOR->red
VOLTAGE_SOURCE->blue
SHORT_CIRCUIT->black
In addition, the user must enter the value of each components by adding an integer label like this: "label=100", meaning that the component have 100 as his value. SHORT_CIRCUIT components, in black color, must have "label=0"
Important notes: ONE PAIR OF VERTEXES CAN NOT HAVE TWO EDGES CONNECTING THEM.
                 ONLY ONE SPACE BETWEEN color AND label IN TEXT INSIDE "[]"
                 
## Examples:
// Parallel: 50V Voltage source + 2 10Ohms resistors
"
graph { node[shape=circle] rankdir=LR
1--2 [color=black, label=0];
3--4 [color=black, label=0];
1--3 [color=blue, label=50];
2--4 [color=red, label=10];
5--6 [color=red, label=10];
2--5 [color=black, label=0];
4--6 [color=black, label=0];
}
"

// Example circuit
"
graph { node[shape=point] rankdir=LR
1--2 [color=black, label=0];
3--4 [color=black, label=0];
1--3 [color=blue, label=50];
2--4 [color=red, label=10];
5--6 [color=red, label=10];
2--5 [color=black, label=0];
4--6 [color=black, label=0];
3--6 [color=blue, label=20];
2--3 [color=red, label=100];
}
"

## 
Feel free to give suggestions.
Thank you for the attention!
