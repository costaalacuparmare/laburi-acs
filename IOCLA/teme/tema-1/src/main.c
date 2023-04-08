#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

int main(int argc, char const *argv[])
{
    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        printf("Unable to read file\n");
        return 0;
    }
    int nr_sensors = 0;
    fread(&(nr_sensors), sizeof(int), 1, input);
    printf("%d\n",nr_sensors);
    sensor *sensors = (sensor *) malloc(nr_sensors * sizeof(sensor));
    int i = 0;
    for (; i < nr_sensors; i++) {
        fread(&sensors[i].sensor_type, sizeof(int), 1, input);
        if (sensors[i].sensor_type)
            fread(&sensors[i].sensor_data, sizeof(power_management_unit), 1, input);
        else
            fread(&sensors[i].sensor_data, sizeof(tire_sensor), 1, input);
        fread(&sensors[i].nr_operations, sizeof(sensors[i].nr_operations), 1, input);
        int j = 0;
        for(; j < sensors[i].nr_operations; j++)
            fread(&sensors[i].operations_idxs[j], sizeof(sensors[i].operations_idxs), 1, input);
    }
    //fscanf(input,"%d",&vector->nr_operations);
    fclose(input);
    free(sensors);
    return 0;
}
