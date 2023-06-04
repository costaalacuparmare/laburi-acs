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

- For the second task, using a vertices array with contains elements of the 
  vertices structure type, created a function that reads from the input file
  the depth for each vertex 

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

- `FreeV` frees the heap memory allocated for the vertices array

#### Edge functions 

- `addEdge` adds the edge in the list of the vertex from where it is originated, 
sorting upwards based on the codification of the vertices


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
For the first task, after the implementation steps of the algorithm, the code
doubles the number of edges, uses DFS to determine how many connected components
are in the given graph and using the safe DFS algorithm to determine the first
vertex of each zone, so that, using the lazy prim algorithm, it can determine
the minimal cost for the renovated roads in each zone. The lazy prim algorithm
also required the implementation of a priority queue, represented by a simple
chained list
```
- `double_edges` doubles the number of edges for the undirected graph


- `DFS` DFS algorithm used to determine the number of connected components
and the beginning of each connected zone


- `getZones` determines the number of connected zones using DFS and
gets the first vertex of each zone


- `PushListPrim` adds an edge to the priority queue, sorting the elements
by the cost


- `PopListPrim` removes from the priority queue all the edges that point
to a given destination


- `PopFirstEdge` extracts the edge with the highest priority. Because the list
is sorted, the edge will always be the first one


- `cmp` comparison function used for qsort


- `lazy_prim` implementation of lazy prim algorithm:
start marks the beginning of each connected zone, and visited marks the
visitation of each vertex; adds in the priority queue all the edges from
start which have as destination an unvisited vertex; chooses the highest
priority edge and start becomes the edge's destination; removes from priority
queue all the edges which have as destination start; adds the edge's cost,
if the edge points to an already visited vertex it returns the array of costs
otherwise it repeats the algorithm.


- `task1` implements the following steps: doubles the edges, calculates the 
number of connected zones, the minimal cost for each and prints them
in the output file

## Task 2
```
For the second task, the vertices array receive the depth from the input file
and also the treasure weight. The code uses the dijkstra algorithm to calculate
the shortest path from the island to the ship, prints the path, the overall
cost of the path, the maximum depth of the ship and the trips needed to carry
the whole treasure to the ship as well as determines if the path exists
```
- `getVerticesDepth` return the codification of the vertex and adds the vertex
  in the vertices array if it wasn't already added


- `dijkstra` implementation of the dijkstra algorithm using the score given:
visited is used to check the visitation of vertices; previous memorises the
vertex before the current one in order to return to it; score array contains
the added up score until the index vertex; verifies the minimal score to update
it each iteration, if the score of the next edge is and the previous scores
are below the added up score in the destination, it replaces it; if no path was
found, returns -1 and frees heap allocated memory; calculates the length of the
path and returns it


- `task2` uses the dijkstra algorithm to calculate the shortest path from the 
island to the ship, prints the path, the overall cost of the path, the maximum
depth of the ship and the trips needed to carry the whole treasure to the ship
as well as determines if the path exists