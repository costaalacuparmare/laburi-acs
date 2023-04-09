#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#define MAX 20

FILE *InitF(char const *argv[]);
sensor *InitS(int nr_sensors);
void print(sensor *sensors, int i);
void Read(sensor *sensors,  int nr_sensors, FILE *input);
char *Read_CMD(int *i);
void Run_CMD(sensor *sensors, int nr_sensors, char *cmd, int i);
void Free(sensor *sensors, int nr_sensors, char *cmd);