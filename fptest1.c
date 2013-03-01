#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#define _GNU_SOURCE
#include <fenv.h> /* C99-specific */

 int i;

void sigfpe_handler(int sig) {
	printf("Received floating-point exception signal (SIGFPE).  Good.\n");
	i=1;
}

int main() {
	double bad;
	double post_bad[10];
	fenv_t envp;

	signal(SIGFPE,sigfpe_handler);

	//feenableexcept(FE_DIVBYZERO);

        bad = 1;

        printf("Why didn't we crash?\n");


        for (i=-5;i<5;i++){

		post_bad[i] = bad/i;
//		if(isnan(post_bad[i])!=0)post_bad[i]=0.0000001;
//		if(isinf(post_bad[i])!=0)post_bad[i]=0.0000001;
	printf("%f\n", post_bad[i]);
	}
	
	return 1;
}
