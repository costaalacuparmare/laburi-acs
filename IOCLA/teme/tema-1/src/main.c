#include "functions.h"

int main(int argc, char const *argv[])
{
    FILE *input = InitF(argv);
    int nr_sensors = 0;
    fread(&nr_sensors, sizeof(int), 1, input);
    printf("%d\n",nr_sensors);
    sensor *sensors = InitS(nr_sensors);
    Read(sensors, nr_sensors, input);
    for (int i = 0; i < nr_sensors; i++) {
        free(sensors[i].sensor_data);
        free(sensors[i].operations_idxs);
    }
    free(sensors);
    return 0;

}
