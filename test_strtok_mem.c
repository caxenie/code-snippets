#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SIZE_BUFFER 200

int main(int argc, char *argv[]){
	
	char *string_buffer = (char*) calloc(MAX_SIZE_BUFFER, sizeof(char));
	char *buf_head = string_buffer;
	char *buf_tail = NULL;
	double val;

	buf_tail = strtok(argv[1],",");
	val = strtod(buf_tail, NULL);
	printf("val: %lf\n", val);

	if(buf_head!=NULL) free(buf_head);

	return EXIT_SUCCESS;
}
