#include "functions.h"

int main(int argc, char const *argv[])
{
    FILE *input = InitF(argv);
    int nr_sensors = 0;
    fread(&nr_sensors, sizeof(int), 1, input);
    sensor *sensors = InitS(nr_sensors);
    Read(sensors, nr_sensors, input);
    Free(nr_sensors, sensors);
    return 0;

}
