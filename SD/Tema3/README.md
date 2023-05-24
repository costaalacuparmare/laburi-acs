# Data Structures & Algorithms - 3rd Homework

### Constantinescu Vlad 314CB

> ***Note: the readme was written using markdown rules, but the checker does
> not recognise the README with the ".md" extension***

The archive contains:
 
- main.c: main of the program
- auxiliary.c: implementation of I/O and auxiliary functions
- graph.c: implementation of graph and edge functions
- vertices.c: implementation of vertices functions
- task1.c: implementation of functions used to solve the 1st task
- task2.c : implementation of functions used to solve the 2nd task
- functions.h: headers for libraries and implementation
functions (I/O, auxiliary, edge, graph, vertices)
- structs.h: the structures used for the program
- Makefile: has build, run, clean and valgrind rules; the run rule must be 
modified with the task desired, since it is received as argument to the executable
- README: explains the homework implementation

Local score: 120/100

## Implementation
```     
- Read the input using the two I/O functions and used a two functions to create
  and add an edge in the graph, memorising the vertices using a separate structure
  that identifies the codification with the vertex's name

- For the second task, using a vertices array with contains elements of the vertices
  structure type, created a function that reads from the input file the depth
  for each vertex 

- Created a function the allocates memory with calloc using the given dimension
```
#### Auxiliary functions

- `openIn` opens the input file and checks if it was opened correctly


- `openOut` opens the output file and checks if it was opened correctly


- `get_size_array` allocates memory with calloc using the given dimension and 
verifies correct allocation

#### Vertices functions

- `InitV` initialises the vertices array


- `getVerticesCode` return the codification of the vertex and adds the vertex
in the vertices array if it wasn't already added


- `addVerticesDepth` return the codification of the vertex and adds the vertex
in the vertices array if it wasn't already added


- `FreeV` frees the heap memory allocated for the vertices array

#### Edge functions 

- `addEdge` adds the edge in the list of the vertex from where it is originated, sorting 
upwards based on the codification of the vertices


- `getEdge` uses vertices function to determine the codification of the
current vertex and the destination of the edge
and then uses the function above to add the edge

#### Graph functions


- `InitG` initialises the graph variable and the edge lists


- `getGraph` uses temporary strings to read the names and fills the graph
with the edges and the cost using edge functions


- `FreeG` frees the heap memory allocated for the graph

## Task 1
```
I wanted to make this awsome so this is me trying
```
- `double_edges` bla bla bla


- `DFS` bla bla bla


- `getZones`


- `PushListPrim`


- `PopListPrim` 


- `PopFirstEdge`


- `cmp`


- `lazy_prim`


- `task1`

## Task 2
```
blah
```
- `getVerticesDepth`


- `dijkstra`


- `task2`