#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int ragc, char** argv){

	int angle = atoi(argv[1]);
	int pangle = 0.0f;
		pangle = angle+180;
	printf("C [-180 - 180] = %d ==> Cp [0 - 360] = %d\n", angle, pangle);
	return 0;
}
