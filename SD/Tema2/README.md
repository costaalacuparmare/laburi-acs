## Compression Quad Tree ##

####  CONSTANTINESCU Vlad 314CB - checker result: 80p + 20p VALGRIND locally ####

This is a short explanation of the contents of the archive and my implementaIption

1. CONTENTS:

 
    - main.c : - reads I/O files
               - initializations, gets the quad tree from the input file
                using the arguments given, selects the task
               - frees memory allocated 
    - auxiliary.c: - compressed quad tree auxiliary functions
                   - I/O auxiliary functions
                   - implementation functions
    - grid.c : - initialization of the grid/ pixel array function
               - reading the grid/ pixel array from .ppm file function
               - freeing the memory allocated for the grid/ pixel array function
    - queue.c : - initialization of queue function
                - adding an element to queue function
                - extracting an element from queue function
                - freeing allocated memory for queue function
    - stats.c : - getting the number of levels from the compression tree function
                - getting the number of leafs from the compression tree function
                - getting the level of the highest leaf from the compression tree function
                - printing in file the nr. of level, nr. of leafs, least compression function
    - compress.c : - printing in binary file the size of image, type of node and BFS of tree function
    - decompress.c : - reading a node from compressed file function
                     - building the quad tree function
                     - getting the quad tree using a queue function
                     - creating image in array of pixels from tree function
                     - writing array of pixels into .ppm file function
                     - writing header and image in .ppm file function
    - quadtree.h : - MACROS
                   - used libraries 
                   - headers for functions from all .c files
                   - structures for pixel, quad tree and queue
2. IMPLEMENTATION:


    - I/O: based on arguments, I preffered to use two function to read the input and output files
    according to the case and the placement of filepath in CLI arguments
    - if the requested tasks are either -c1 or -c2, we know the input file is of type .pmm, therefore
    it is required to read the header and after that, the image, placed in a pixel array named size, later
    used to extract the pixels based on average and mean, calculated by the given formulas, to determine the
    compression tree
    - if the requested task is -d, we know the input file is a compression file consisting of the BFS of the
    compression tree, therefore we use a queue to complete the quad tree and rearange the nodes in the tree,
    based on their types and order in the file
    - for task1/ stats: 3 functions which determine the needed information. For the third piece of information
    I considered the best approach is to divide the initial size to 2 ^ level of highest leaf, given that
    the compression is divided by 2 each level of the compression tree
    - for task2/ compression: I used a queue to remember the children of parents from the quad tree and to
    implement the BFS of the tree to printf in the output file.
    - for task3/ decompression: I considered this to be the combined reverse process of tasks 1 and 2.
    Firstly, I use two functions to read the type and, if node is a leaf, the RGB values of each node from
    the compressed file. If the type was 0, the children are read and placed in an auxiliary queue, thus
    completing the tree. Afterwards, i place the elements from the tree in grid, a pixel array, reversing the
    proccess of reading the file for cases -c1, -c2. Continuing, I print the specific header for the .ppm type
    file and I print the grid.
    - I decided to distribute my code in multiple source files with suggestive names in order to make it
    easy to find functions related to grid/ queue/ tasks/ etc.