// THIS ARE THE FUNCTIONS FOR THE TASKS
#include "functions.h"

FILE *InitF(char const *argv[]) {
    FILE *input = fopen(/*argv[1]*/"sensors_print_easy_1.dat", "rb");
    if (!input) {
        printf("Unable to read file\n");
        return NULL;
    }
    return input;
}

sensor *InitS(int nr_sensors) {
    sensor *sensors = (sensor *) malloc(nr_sensors * sizeof(sensor));
    if(!sensors) {
        printf("Error at malloc sensors\n");
        return NULL;
    }
    return sensors;
}

void Read(sensor *sensors, int nr_sensors, FILE *input) {
    int i = 0;
    for (; i < nr_sensors; i++) {
        fread(&sensors[i].sensor_type, sizeof(sensors[i].sensor_type), 1, input);
        if (sensors[i].sensor_type) {
            sensors[i].sensor_data = malloc(sizeof(power_management_unit));
            if (!sensors[i].sensor_data) {
                printf("Error at malloc sensor_data, element %d\n", i);
                return;
            }
            fread(sensors[i].sensor_data, sizeof(power_management_unit), 1, input);
        }
        else {
            sensors[i].sensor_data = malloc(sizeof(tire_sensor));
            if (!sensors[i].sensor_data) {
                printf("Error at malloc sensor_data, element %d\n", i);
                return;
            }
            fread(sensors[i].sensor_data, sizeof(tire_sensor), 1, input);
        }
        fread(&sensors[i].nr_operations, sizeof(sensors[i].nr_operations), 1, input);
        sensors[i].operations_idxs = (int *) malloc(sensors[i].nr_operations * sizeof(int));
        if (!sensors[i].operations_idxs) {
            printf("Error at malloc operations_idxs, element %d\n", i);
            return;
        }
        int j = 0;
        for(; j < sensors[i].nr_operations; j++)
            fread(&sensors[i].operations_idxs[j], sizeof(sensors[i].operations_idxs[j]), 1, input);
    }
    fclose(input);
}

void Free(int nr_sensors, sensor *sensors) {
    for (int i = 0; i < nr_sensors; i++) {
        free(sensors[i].sensor_data);
        free(sensors[i].operations_idxs);
    }
    free(sensors);
}