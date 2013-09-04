#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAL_SIGN	1
#define VAL_NUMB	5
#define VALUE_LEN	VAL_SIGN+VAL_NUMB

#define MASK_GYROZ		41
#define MASK_WHL_ONE		6
#define MASK_WHL_TWO		13
#define MASK_WHL_THREE		20	
#define MASK_COMPH		69
#define RING_BUFFER_SIZE 	 8

#define VAL_TRACK_MAX_LEN	10

int main(int argc, char*argv[])
{

	char* test = "-I38: +00001 +00002 +00003 +00000 +00000 +00099 +00000 +00123 -00138 -00168\n";
	printf("Size is : %d \n", strlen(test));

	printf("GYRO RAW %s\n", strndup(test+MASK_GYROZ, VALUE_LEN), NULL);
        printf("WH1 RAW %s\n", strndup(test+MASK_WHL_ONE, VALUE_LEN), NULL);
        printf("WH2 RAW %s\n", strndup(test+MASK_WHL_TWO, VALUE_LEN), NULL);
        printf("WH3 RAW %s\n", strndup(test+MASK_WHL_THREE, VALUE_LEN), NULL);
        printf("COMPH RAW %s\n", strndup(test+MASK_COMPH, VALUE_LEN), NULL);


	printf("GYRO %lf\n", strtod(strndup(test+MASK_GYROZ, VALUE_LEN), NULL)/RING_BUFFER_SIZE);
	printf("WH1 %lf\n", strtod(strndup(test+MASK_WHL_ONE, VALUE_LEN), NULL)/RING_BUFFER_SIZE);
	printf("WH2 %lf\n", strtod(strndup(test+MASK_WHL_TWO, VALUE_LEN), NULL)/RING_BUFFER_SIZE);
	printf("WH3 %lf\n", strtod(strndup(test+MASK_WHL_THREE, VALUE_LEN), NULL)/RING_BUFFER_SIZE);
	printf("COMPH %lf\n", strtod(strndup(test+MASK_COMPH, VALUE_LEN), NULL)/RING_BUFFER_SIZE);
	
	char* cur_line = "31.360044,-24.940010,285.708649,278,1378230110727855592";
	char trkx[VAL_TRACK_MAX_LEN], 
	     trky[VAL_TRACK_MAX_LEN], 
	     trkh[VAL_TRACK_MAX_LEN], 
	     trkiter[VAL_TRACK_MAX_LEN], 
             trkts[5*VAL_TRACK_MAX_LEN];

	sscanf(cur_line, "%[^','],%[^','],%[^','],%s", trkx, trky, trkh, trkiter, trkts);
        printf("%lf, %lf, %lf\n", strtod(trkx, NULL), strtod(trky, NULL), strtod(trkh, NULL));
	
	
	return EXIT_SUCCESS;
}
