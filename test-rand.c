#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){

	int i = 100, rand_map = 0, rand_edge = 0;

	while(--i){
	
		rand_map = rand() % 3 + 1;
		

		switch(rand_map){
			case 1:
				rand_edge = rand() % 2 + 1;
			        printf("LINKS2: Iter[%d] - Rand_Map[%d] - Rand_Edge[%d]\n", i, rand_map, rand_edge);
			break;
			case 2:
				rand_edge = rand() % 3 + 1;
                                printf("LINKS3: Iter[%d] - Rand_Map[%d] - Rand_Edge[%d]\n", i, rand_map, rand_edge);
			break;
			case 3:
				rand_edge = rand() % 4 + 1;
                                printf("LINKS4: Iter[%d] - Rand_Map[%d] - Rand_Edge[%d]\n", i, rand_map, rand_edge);
			break;
			
		}	
	}
 	printf("Numbers test\n");
	double num = -124.00f;
	double num1 = 55.00f;
	printf("first number test %lf\n", num);
	if(num > 0) printf("pos: %lf\n", num);
	if(num < 0) printf("neg: add 360 : %lf\n", num+360.0);
	printf("second number test %lf\n", num1);
	if(num1 > 0) printf("pos: %lf\n", num1);
        if(num1 < 0) printf("neg: add 360 : %lf\n", num1+360.0);
	return 0;
}
