/* These are the functions we use for solving the homework */
#include "functions.h"

/* Initialisation functions */

/* Returns the input binary file passed as argument from main */
FILE *InitF(char const *argv[])
{
	FILE *input = fopen(argv[1], "rb");
	if (!input) {
		printf("Unable to read file\n");
	}
	return input;
}

/* Initialises the sensors array with the number
 * of sensors read in main */
sensor *InitS(int nr_sensors)
{
	sensor *sensors = (sensor *) malloc(nr_sensors * sizeof(sensor));
	if (!sensors) {
		printf("Error at malloc sensors\n");
	}
	return sensors;
}

/* Commands required to fix the sensors */

/* Auxiliary function that sorts the
 * sensor array based on priority
 * 1 = pmu, 0 = tire */
int cmp(const void *a, const void *b)
{
	sensor *ax = (sensor *) a;
	sensor *bx = (sensor *) b;
	return ((int)(bx->sensor_type - ax->sensor_type));
}

/* Auxiliary function that checks the
 * parameters of sensors and verifies
 * if they should be removed or not */
int condition(sensor *sensors, int i)
{
	if (sensors[i].sensor_type) {
		power_management_unit *pmu = NULL;
		pmu = (power_management_unit *) sensors[i].sensor_data;
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
		tire_sensor *tire = NULL;
		tire = (tire_sensor *) sensors[i].sensor_data;
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

/* Prints specified sensor */
void print(sensor *sensors, int i)
{
	if (sensors[i].sensor_type) {
		printf("Power Management Unit\n");
		power_management_unit *pmu = NULL;
		pmu = (power_management_unit *) sensors[i].sensor_data;
		printf("Voltage: %.2f\n", pmu->voltage);
		printf("Current: %.2f\n", pmu->current);
		printf("Power Consumption: %.2f\n", pmu->power_consumption);
		printf("Energy Regen: %d%%\n", pmu->energy_regen);
		printf("Energy Storage: %d%%\n", pmu->energy_storage);
	} else {
		printf("Tire Sensor\n");
		tire_sensor *tire = NULL;
		tire = (tire_sensor *) sensors[i].sensor_data;
		printf("Pressure: %.2f\n", tire->pressure);
		printf("Temperature: %.2f\n", tire->temperature);
		printf("Wear Level: %d%%\n", tire->wear_level);
		if (tire->performace_score == 0)
			printf("Performance Score: Not Calculated\n");
		else
			printf("Performance Score: %d\n", tire->performace_score);
	}
}

/* Analyses sensors and executes the
 * operations that are needed to fix
 * said sensors */
void analyse(sensor *sensors, int i)
{
	/* Uses an array of pointers at functions
	 * and the indexes of the operations given
	 * from the input binary file */
	void (*operations[NR_OPERATIONS])(void *) = {};
	get_operations((void **)operations);
	for (int j = 0; j < sensors[i].nr_operations; j++)
		operations[sensors[i].operations_idxs[j]](sensors[i].sensor_data);
}

/* Deletes sensors that are found to be
 * outside of parameters be clearing memory
 * and overwriting element by element
 * after the sensor that is faulty */
void clear(sensor *sensors, int *nr_sensors)
{
	int i = 0;
	while (i < (*nr_sensors)) {
		if (condition(sensors, i)) {
			if (sensors[i].sensor_data != NULL) {
				free(sensors[i].sensor_data);
				sensors[i].sensor_data = NULL;
			}
			if (sensors[i].operations_idxs != NULL) {
				free(sensors[i].operations_idxs);
				sensors[i].operations_idxs = NULL;
			}
			int size = sizeof(sensor);
			memmove(sensors+i, sensors+i+1, ((*nr_sensors)-i-1) * size);
			(*nr_sensors)--;
		} else {
			i++;
		}
	}
}

/* Implementation functions */

/* Inserts the sensors from the input file in the sensor
 * array and gets the sensor data based on their type */
void Read(sensor *sensors, int nr_sensors, FILE *input)
{
	for (int i = 0; i < nr_sensors; i++) {
		fread(&sensors[i].sensor_type, sizeof(int), 1, input);
		if (sensors[i].sensor_type) {
			sensors[i].sensor_data = malloc(sizeof(power_management_unit));
			if (!sensors[i].sensor_data) {
				printf("Error at malloc sensor_data, sensor %d\n", i);
				return;
			}
			int pmu = sizeof(power_management_unit);
			fread(sensors[i].sensor_data, pmu, 1, input);
		} else {
			sensors[i].sensor_data = malloc(sizeof(tire_sensor));
			if (!sensors[i].sensor_data) {
				printf("Error at malloc sensor_data, sensor %d\n", i);
				return;
			}
			fread(sensors[i].sensor_data, sizeof(tire_sensor), 1, input);
		}
		fread(&sensors[i].nr_operations, sizeof(int), 1, input);
		int nr_op = sensors[i].nr_operations;
		sensors[i].operations_idxs = (int *) malloc(nr_op * sizeof(int));
		if (!sensors[i].operations_idxs) {
			printf("Error at malloc operations_idxs, element %d\n", i);
			return;
		}
		for (int j = 0; j < sensors[i].nr_operations; j++)
			fread(&sensors[i].operations_idxs[j], sizeof(int), 1, input);
	}

	/*sorts the sensors based on their priority
	 * using the cmp auxiliary function */
	qsort(sensors, nr_sensors, sizeof(sensor), cmp);
	fclose(input);
}

/* Reads the commands from keyboard and separates
 * the index, if necessary */
char *Read_CMD(int *i)
{
	char *cmd = (char *) malloc(MAX * sizeof(char));
	if (!cmd) {
		printf("Error at command malloc in Read_CMD\n");
		return NULL;
	}
	fgets(cmd, MAX, stdin);

	/* Only commands exit and clear don't have indexes.
	 * The second 'if' makes sure that indexes are numerical,
	 * 'else' makes the index negative, making it out of bounds */
	if (strcmp(cmd, "exit\n") || strcmp(cmd, "clear\n")) {
		if ('0' <= cmd[strlen(cmd) - 2] && cmd[strlen(cmd) - 2] <= '9')
			(*i) = atoi(strchr(cmd, ' '));
		else
			(*i) = -1;
	}

	/* separates the input from the index */
	cmd = strtok(cmd, " ");
	return cmd;
}

/* Verifies that indexes are available for the sensor array
 * and runs the command desired */
void Run_CMD(sensor *sensors, int *nr_sensors, char *cmd, int i)
{
	if (i > (*nr_sensors) || i < 0) {
		if (strcmp(cmd, "clear\n")) {
			printf("Index not in range!\n");
			free(cmd);
			return;
		}
	}
	if (!strcmp(cmd, "print"))
		print(sensors, i);
	if (!strcmp(cmd, "analyze"))
		analyse(sensors, i);
	if (!strcmp(cmd, "clear\n")) {
		clear(sensors, nr_sensors);
	}
	free(cmd);
}

/* Frees the memory after all commands are executed */
void Free(sensor *sensors, int nr_sensors, char *cmd)
{
	for (int i = 0; i < nr_sensors; i++) {
		free(sensors[i].sensor_data);
		free(sensors[i].operations_idxs);
	}
	free(sensors);
	free(cmd);
}
