#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/* MACROS used for parameters
 * of sensor fields */
#define MIN_V 10
#define MAX_V 20
#define MIN_A -100
#define MAX_A 100
#define MAX_KW 1000
#define MAX_PERCENTAGE 100
#define MIN_PSI 19
#define MAX_PSI 28
#define MAX_CELSIUS 120

/* MACROS used for commands
 * and operations */
#define MAX 20
#define NR_OPERATIONS 8

/* Initialisation functions */
FILE *InitF(char const *argv[]);
sensor *InitS(int nr_sensors);

/* Auxiliary functions for commands */
int cmp(const void *a, const void *b);
int condition(sensor *sensors, int i);
void get_operations(void **operations);

/* Commands functions */
void print(sensor *sensors, int i);
void analyse(sensor *sensors, int i);
void clear(sensor *s, int *nr_sensors);

/* Implementation functions */
void Read(sensor *sensors, int nr_sensors, FILE *input);
char *Read_CMD(int *i);
void Run_CMD(sensor *sensors, int *nr_sensors, char *cmd, int i);
void Free(sensor *sensors, int nr_sensors, char *cmd);
