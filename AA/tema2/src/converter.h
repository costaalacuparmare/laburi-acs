#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* declared MACROS for limiting the sizes of arrays */

#define MAX_PORTS 100
#define MAX_INPUTS 60
#define MAX_VARIABLES (MAX_PORTS + 1)
#define MAX_CLAUSES (MAX_PORTS * 3)

/* defined port structure */
typedef struct {
	char type[4]; // AND, OR, NOT
	int inputs[MAX_INPUTS];
	int numInputs;
	int output;
} Port;

/* defined circuit structure */
typedef struct {
	int numInputs;
	int numPorts;
	int output;
	Port ports[MAX_PORTS];
} Circuit;

/* defined CNF-SAT formula structure */
typedef struct {
	int numVariables;
	int numClauses;
	int clauses[MAX_CLAUSES][MAX_VARIABLES];
} CNFSATForm;
