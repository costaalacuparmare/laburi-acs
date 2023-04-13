#include "functions.h"

int main(int argc, char const *argv[]) {
    FILE *input = InitF(argv);

    int nr_sensors = 0;
    fread(&nr_sensors, sizeof(int), 1, input);

    sensor *sensors = InitS(nr_sensors);
    Read(sensors, nr_sensors, input);

    /* reads commands from keyboard individually
     * and runs them as long as they're not exit */
    int i = 0;
    char *cmd = Read_CMD(&i);
    while (strcmp(cmd, "exit\n")) {
        Run_CMD(sensors, &nr_sensors, cmd, i);
        cmd = Read_CMD(&i);
    }

    Free(sensors, nr_sensors, cmd);
    return 0;
}
