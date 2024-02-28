#include "converter.h"

/* reads circuit from input file with specified format */
Circuit read_circuit_from_file(const char *filename) {

	/* open file */
	FILE *file = fopen(filename, "r");

	if (file == NULL) {
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}

	/* read circuit */
	Circuit circuit;

	circuit.numInputs = 0;
	fscanf(file, "%d %d", &circuit.numInputs, &circuit.output);
	circuit.numPorts = circuit.output - circuit.numInputs;
	for (int i = 0; i < circuit.numPorts; i++) {
		fscanf(file, "%s", circuit.ports[i].type);
		int j = 0;
		while (fscanf(file, "%d", &circuit.ports[i].inputs[j]) == 1)
			j++;
		circuit.ports[i].output = circuit.ports[i].inputs[j - 1];
		circuit.ports[i].inputs[j - 1] = 0;
		circuit.ports[i].numInputs = j - 1;
	}

	/* close file */
	fclose(file);
	return circuit;
}

/* auxiliary function for adding a clause to CNF-SAT formula */
void reset_inputs(int *inputs) {
	for (int i = 0; i < MAX_INPUTS; i++)
		inputs[i] = 0;
}

/* auxiliary function for adding a clause to CNF-SAT formula */
void add_clause(CNFSATForm *formula, int literal0, int *inputs) {
	formula->clauses[formula->numClauses][0] = literal0;

	/* add inputs to clause not matter the type of port */
	int i = 0;

	while (i < MAX_INPUTS && inputs[i] != 0) {
		formula->clauses[formula->numClauses][i+1] = inputs[i];
		i++;
	}
	formula->numClauses++;
}

/* converts circuit to CNF-SAT formula */
CNFSATForm polynomial_reduction(Circuit circuit) {
	CNFSATForm formula;

	/* number of variables shouldn't be greater than number of inputs + number of ports */
	formula.numVariables = circuit.numInputs + circuit.numPorts;
	formula.numClauses = 0;

	/* add clauses for each port type */
	for (int i = 0; i < circuit.numPorts; i++) {
		Port port = circuit.ports[i];
		int inputs[MAX_INPUTS];

		/* add clauses for AND port */
		if (strcmp(port.type, "AND") == 0) {
			for (int j = 0; j < port.numInputs; j++)
				inputs[j] = -port.inputs[j];
			add_clause(&formula, port.output, inputs);
			reset_inputs(inputs);
			for (int j = 0; j < port.numInputs; j++) {
				inputs[0] = port.inputs[j];
				add_clause(&formula, -port.output, inputs);
			}
			/* add clauses for OR port */
		} else if (strcmp(port.type, "OR") == 0) {
			for (int j = 0; j < port.numInputs; j++)
				inputs[j] = port.inputs[j];
			add_clause(&formula, -port.output, inputs);
			reset_inputs(inputs);
			for (int j = 0; j < port.numInputs; j++) {
				inputs[0] = -port.inputs[j];
				add_clause(&formula, port.output, inputs);
			}
			/* add clauses for NOT port */
		} else if (strcmp(port.type, "NOT") == 0) {
			reset_inputs(inputs);
			inputs[0] = port.inputs[0];
			add_clause(&formula, port.output, inputs);
			inputs[0] = -port.inputs[0];
			add_clause(&formula, -port.output, inputs);
		}
	}
	return formula;
}

/* prints CNF-SAT formula to output file with specified format */
void printCNFSAT(CNFSATForm formula, FILE *output_file) {
	fprintf(output_file, "p cnf %d %d\n", formula.numVariables, formula.numClauses);
	for (int i = 0; i < formula.numClauses - 1; i++) {
		int j = 0;

		while (j < formula.numVariables && formula.clauses[i][j] != 0) {
			fprintf(output_file, "%d ", formula.clauses[i][j]);
			j++;
		}
		/* print 0 at the end of each clause */
		fprintf(output_file, "0\n");
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input_file> <output_file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	Circuit circuit = read_circuit_from_file(argv[1]);

	CNFSATForm formula = polynomial_reduction(circuit);

	/* print CNF-SAT formula to output file */
	FILE *output_file = fopen(argv[2], "w");

	/* add clause for output */
	formula.numClauses++;
	printCNFSAT(formula, output_file);
	fprintf(output_file, "%d 0\n", circuit.output);
	fclose(output_file);

	return 0;
}
