/* These are the functions we use for solving the homework */
#include "functions.h"

FILE *InitF(char const *argv[]) {
    FILE *input = fopen(argv[1], "rb");
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

int condition(sensor *sensors, int i) {
    if (sensors[i].sensor_type) {
        power_management_unit *pmu = (power_management_unit *) sensors[i].sensor_data;
        if (pmu->voltage < MIN_V || pmu->voltage > MAX_V) {
            return 1;
        }
        if (pmu->current < MIN_A || pmu->current > MAX_A) {
            return 1;
        }
        if (pmu->power_consumption < 0 || pmu->power_consumption > MAX_KW) {
            return 1;
        }
        if (pmu->energy_storage < 0 || pmu->energy_storage > MAX_PERCENTAGE) {
            return 1;
        }
        if (pmu->energy_regen < 0 || pmu->energy_regen > MAX_PERCENTAGE) {
            return 1;
        }
    } else {
        tire_sensor *tire = (tire_sensor *) sensors[i].sensor_data;
        if (tire->pressure < MIN_PSI || tire->pressure > MAX_PSI) {
            return 1;
        }
        if (tire->temperature < 0 || tire->temperature > MAX_CELSIUS) {
            return 1;
        }
        if (tire->wear_level < 0 || tire->wear_level > MAX_PERCENTAGE) {
            return 1;
        }
    }
    return 0;
}

void print(sensor *sensors, int i) {
    if (sensors[i].sensor_type) {
        printf("Power Management Unit\n");
        printf("Voltage: %.2f\n", ((power_management_unit *) sensors[i].sensor_data)->voltage);
        printf("Current: %.2f\n", ((power_management_unit *) sensors[i].sensor_data)->current);
        printf("Power Consumption: %.2f\n", ((power_management_unit *) sensors[i].sensor_data)->power_consumption);
        printf("Energy Regen: %d%%\n", ((power_management_unit *) sensors[i].sensor_data)->energy_regen);
        printf("Energy Storage: %d%%\n", ((power_management_unit *) sensors[i].sensor_data)->energy_storage);
    }
    else {
        printf("Tire Sensor\n");
        printf("Pressure: %.2f\n", ((tire_sensor *) sensors[i].sensor_data)->pressure);
        printf("Temperature: %.2f\n", ((tire_sensor *) sensors[i].sensor_data)->temperature);
        printf("Wear Level: %d%%\n", ((tire_sensor *) sensors[i].sensor_data)->wear_level);
        if (((tire_sensor *) sensors[i].sensor_data)->performace_score == 0)
            printf("Performance Score: Not Calculated\n");
        else
            printf("Performance Score: %d\n", ((tire_sensor *) sensors[i].sensor_data)->performace_score);
    }
}

void analyse(sensor *sensors, int i) {
    //void **operations = (void **) malloc(8 * sizeof(void *));
    void (*operations[8])(void *) = {};
    get_operations((void **)operations);
    for (int j = 0; j < sensors[i].nr_operations; j++)
        operations[sensors[i].operations_idxs[j]](sensors[i].sensor_data);
}

void clear(sensor *sensors, int *nr_sensors) {
    int i = 0;
    while( i < (*nr_sensors))
        if (condition(sensors,i)) {
            if (sensors[i].sensor_data != NULL)
                free(sensors[i].sensor_data);
            if (sensors[i].operations_idxs != NULL)
                free(sensors[i].operations_idxs);
            for (int j = i; j < (*nr_sensors)-1; j++)
                sensors[j] = sensors[j+1];
            (*nr_sensors)--;
        }
        else
            i++;
}

int cmp(const void *a, const void *b) {
    sensor *ax = (sensor *) a;
    sensor *bx = (sensor *) b;
    return (bx->sensor_type - ax->sensor_type);
}

void Read(sensor *sensors, int nr_sensors, FILE *input) {
    for (int i = 0; i < nr_sensors; i++) {
        fread(&sensors[i].sensor_type, sizeof(sensors[i].sensor_type), 1, input);
        if (sensors[i].sensor_type) {
            sensors[i].sensor_data = malloc(sizeof(power_management_unit));
            if (!sensors[i].sensor_data) {
                printf("Error at malloc sensor_data, sensor %d\n", i);
                return;
            }
            fread(sensors[i].sensor_data, sizeof(power_management_unit), 1, input);
        }
        else {
            sensors[i].sensor_data = malloc(sizeof(tire_sensor));
            if (!sensors[i].sensor_data) {
                printf("Error at malloc sensor_data, sensor %d\n", i);
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
        for (int j = 0; j < sensors[i].nr_operations; j++)
            fread(&sensors[i].operations_idxs[j], sizeof(sensors[i].operations_idxs[j]), 1, input);
    }
    qsort(sensors,nr_sensors,sizeof(sensor), cmp);
    fclose(input);
}

char *Read_CMD(int *i) {
    char *cmd = (char *) malloc(MAX * sizeof(char));
    if (!cmd) {
        printf("Error at command malloc in Read_CMD\n");
        return NULL;
    }
    fgets(cmd, MAX, stdin);
    if (strcmp(cmd, "exit\n") || strcmp(cmd, "clear\n")) {
        if ('0' <= cmd[strlen(cmd) - 2] && cmd[strlen(cmd) - 2] <= '9')
            (*i) = atoi(strchr(cmd, ' '));
        else
            (*i) = -1;
    }
    cmd = strtok(cmd, " ");
    return cmd;
}

void Run_CMD(sensor *sensors, int *nr_sensors, char *cmd, int i) {
    if (i > (*nr_sensors) || i < 0)
        if(strcmp(cmd,"clear\n")) {
            printf("Index not in range!\n");
            free(cmd);
            return;
        }
    if(!strcmp(cmd,"print"))
        print(sensors, i);
    if(!strcmp(cmd,"analyze"))
        analyse(sensors, i);
    if(!strcmp(cmd,"clear\n"))
        clear(sensors, nr_sensors);
    free(cmd);
}

void Free(sensor *sensors, int nr_sensors, char *cmd) {
    for (int i = 0; i < nr_sensors; i++) {
        free(sensors[i].sensor_data);
        free(sensors[i].operations_idxs);
    }
    free(sensors);
    free(cmd);
}