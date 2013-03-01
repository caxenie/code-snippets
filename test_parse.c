#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char* argv[])
{
	char sensor_rx_buf[200]="-Ib=00 w=+00000 +00000 +00000 c=+03234 -01549 +06972 +00160 a=+01025 -00533 -32735 g=-00002 +00002 -00086 e=+00009 +00014 +00229";
	char *tmp_val[6];
	char *full_packet_info, *eval_packet_info;
	char gyro_data[50], compass_data[50];
	char wheel_data[50];
	//strcpy(gyro_data,"g=");
	//strcpy(compass_data, "c=");
	//strcpy(wheel_data, "wv=");
	full_packet_info = strtok(sensor_rx_buf, "=");
	tmp_val[0] = strtok(NULL, "="); // b
	tmp_val[1] = strtok(NULL, "="); // w
	tmp_val[2] = strtok(NULL, "="); // c
	tmp_val[3] = strtok(NULL, "="); // a
	tmp_val[4] = strtok(NULL, "="); // g
	tmp_val[5] = strtok(NULL, "="); // e
	// extract gyro data: raw yaw data ( rate : deg/s) and euler for yaw
	eval_packet_info = strtok(tmp_val[4], " ");
	eval_packet_info = strtok(NULL, " ");
	eval_packet_info = strtok(NULL, " ");
	strcat(gyro_data, eval_packet_info);
	// extract compass data: heading value
	eval_packet_info = strtok(tmp_val[2], " ");
	eval_packet_info = strtok(NULL, " ");
	eval_packet_info = strtok(NULL, " ");
	eval_packet_info = strtok(NULL, " ");
	strcat(compass_data, eval_packet_info);
	// extract wheel velocities data: w1,w2,w3
	eval_packet_info = strtok(tmp_val[1], " ");
	strcat(wheel_data, eval_packet_info);
	strcat(wheel_data, ",");
	eval_packet_info = strtok(NULL, " ");
	strcat(wheel_data, eval_packet_info);
	strcat(wheel_data, ",");
	eval_packet_info = strtok(NULL, " ");
	strcat(wheel_data, eval_packet_info);

	printf(" GYRO: %s\n COMPASS: %s\n WHEELS: %s \n", gyro_data, compass_data, wheel_data);

	printf(" GYRO(int): %lf\n COMPASS(int): %lf\n WHEELS(int): %lf \n", strtod(gyro_data, NULL), strtod(compass_data, NULL), strtod(wheel_data, NULL));

	return 0;
}
