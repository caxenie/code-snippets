#include <stdio.h>

int main(int argc, char*argv[])
{

    int sensor_iface_pid;
    char line[20];
    FILE *cmd = popen("pidof fusion_maps_sensors_iface", "r");
    fgets(line, 20, cmd);
    sensor_iface_pid = strtoul(line, NULL, 10);
    printf("PID is %d\n", sensor_iface_pid);
    pclose(cmd);

return 0;
}
