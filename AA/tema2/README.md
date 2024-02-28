# Algorithm Analysis - 2nd Homework

### Constantinescu Vlad 324CB

The source folder contains:

- converter.c: contains auxiliary functions for converting between
  representations of the graph and the main function
- converter.h: contains the headers, macros and structures for the functions
  in converter.c
- Makefile: contains the makefile for the project

## General Implementation
- Used [Tseytin transformation](https://en.wikipedia.org/wiki/Tseytin_transformation)
to convert CSAT to CNF-SAT


- In Tseytin transformation, each port is replaced by more clauses
  (for AND, OR and NOT ports). For AND OR ports, the clauses are similar -
  negation of inputs with output, negation of output with inputs, the OR type
  being the opposite (negation of output with inputs, negation of inputs with output)
  and for the NOT port, the clauses are negation of input and output and input and output


- Used structures to represent the circuit, the ports and the CNF-SAT formula


- Used loops to convert the graph to CNF-SAT with the functions detailed below

## Structures & Macros

- `MAX_PORTS`, `MAX_INPUTS`, `MAX_VARIABLES`, `MAX_CLAUSES` are macros for
  the maximum number of ports, inputs, variables and clauses


- `Port` represents a port with its type, inputs, number of inputs and output


- `Circuit` represents a circuit with its number of ports, inputs, its final output
and the array of inputs


- `CNFSATForm` represents a CNF-SAT formula with its number of variables, clauses
  and the array of clauses

## Functions

- `read_circuit_from_file` reads the circuit from the input file and returns
  a Circuit structure


- `reset_inputs` resets the auxiliary inputs array used for adding the clauses
  to the CNF-SAT formula


- `add_clauses` adds the clauses to the CNF-SAT formula using the auxiliary
  inputs array and loops to add the clauses for any gate type and any number
  of inputs


- `polynomial_reduction` reduces the CSAT to CNF-SAT using the Tseytin
  transformation and returns a CNF-SAT formula


- `print_cnf_sat_formula` prints the CNF-SAT formula to the output file


- `main` reads the circuit from the input file, converts it to CNF-SAT and
  prints the CNF-SAT formula to the output file, adding the clause for the output