/* CONSTANTINESCU Vlad 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* MACROs for searching the quad tree */
#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)

/* auxiliary functions */

/* grid functions */

/* grid structure */

/* grid is represented by a square array of pixels */
typedef struct pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} TPixel;

/* grid functions */

/* initializes the grid / pixel array to size * size */
TPixel **InitGrid(unsigned int size);

/* reads the size and grid/ pixel array from the ppm input file */
TPixel **readPPM(TPixel **grid, unsigned int *size, FILE* input);

/* frees the memory allocated for the grid/ pixel array */
void FreeGrid(TPixel **grid, unsigned int size);

/* quad tree */

/* quad tree structure */
typedef struct quad {
	unsigned char type;
	TPixel info;
	struct quad *topL;
	struct quad *topR;
	struct quad *botL;
	struct quad *botR;
} TCellQuad, *TQuad;

/* quad tree functions */

/* build the quad tree using the information stored in the grid and the algorithm
 * of compression given, as well as more auxiliary functions */
TQuad buildQT (TPixel **grid, unsigned int size, int x, int y, int factor);

/* serving as input the compression of an image, the functions creates the quad tree
 * using an auxiliary queue and the information from the input file */
TQuad getQT(FILE * input);

/* queue */

/* queue structure */
typedef struct cellQ {
	TQuad info;
	struct cellQ* next;
} TCellQ, *TListQ;

typedef struct queue {
	TListQ front, rear;
} *TQueue;

/* queue functions */

/* initializes the queue */
TQueue InitQ();

/* adds a command to the queue */
void PushQ(TQueue *Q, TQuad x);

/* removes a command from the queue */
void PopQ(TQueue *Q);

/* frees the heap memory space used for the queue */
void FreeQ(TQueue *Q);

/* I/O functions */

/* based on the task requested in the command line, open
 * the correct input file with the correct format */
FILE *openIn(char const *argv[]);

/* based on the task requested in the command line, open
 * the correct output file with the correct format */
FILE *openOut(char const *argv[]);

/* script options functions */

/* Statistics/ Task1 = determines the levels in the quad tree, the number
 * of leafs and the size of the least compressed leaf */
void stats(TQuad qtree, FILE *output, unsigned int size);

/* Compression/ Task2 = writes in a binary output file the size of the image,
 * as well as the types of nodes and the BFS of the tree */
void compress(TQuad qtree, FILE *output, unsigned int size);

/* Decompression/ Task3 = having as input a file with the same format
 * as the compression file, decompresses the image by using a queue
 * and the BFS of the tree, creating a .ppm type file as output */
void decompress(TQuad qtree, FILE *output, unsigned int size);

/* implementation functions */

/* based on the argument from the command line, runs the requested task */
void getTask(char const *argv[], TQuad qtree, FILE *output, unsigned int size);

/* frees the memory allocated for the quad tree and closes the opened files */
void Free(TQuad *qtree, FILE *input, FILE *output);