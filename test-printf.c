#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){

        int d;
        char* letters = (char*)calloc(10, sizeof(char));
		d=-12431;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=121;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=31;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
        printf("\n");
		d=-131;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=-56464;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=-48;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
        printf("\n");
		d=3453;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=-88911;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
		d=-89545;
		sprintf(letters, "%+d", d);
		printf("%4.4s ",letters);
        printf("\n");
	 if(letters) free(letters);
	return 0;
}
