#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

FILE *InitF(char const *argv[]);
sensor *InitS(int nr_sensors);
void Read(sensor *sensors,  int nr_sensors, FILE *input);