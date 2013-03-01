#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int test_var = 0;

	if(test_var==0){
		 test_var =1+atoi(argv[1]);
		 printf("Incremented test_var\n");
	}

	if(test_var==1) goto label;


	printf("Didn't jump\n");

label:
	printf("Jumped here and reset everything\n");
	test_var = 0;
	
	return EXIT_SUCCESS;
}
