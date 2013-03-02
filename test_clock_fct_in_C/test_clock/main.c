#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <setjmp.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/time.h>
#include <ucontext.h>
#include <time.h>

#define PERIOD 5.0f
#define ERROR 0.001f

int main(void)
{
    /* some timing info */
    struct timespec start, stop;

    char *cmd = "test\n";
    int i = 0;

    while(1){

        /* start time */
        if( clock_gettime( CLOCK_REALTIME , &start) == -1 ) {
            printf( "clock gettime" );
            exit( 1 );
        }

        printf("%s\n", cmd);
        sleep(i);
        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
            perror( "clock gettime" );
            exit( 1 );
        }
        printf("============================\n");
        printf("CLK_I: %d\n", start.tv_sec);
        printf("CLK_F: %d\n", stop.tv_sec);
        printf("DIFF_CLK: %d\n", stop.tv_sec - start.tv_sec);

        if(stop.tv_sec - start.tv_sec == 5){
            cmd = "TEST\n";
        }
        else{
            cmd = "test\n";
        }
        i++;
        if(i==10)i=0;
    }

    return 0;
}

