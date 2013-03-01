#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

enum{
	ONE_SHOT,
	PERIODIC
};

timer_t periodic[3];
timer_t oneshot1, oneshot2;


void
timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    if ( *tidp == periodic[0] )
        printf("first_timer \n");
    else if ( *tidp == periodic[1] )
		printf("second_timer \n");
    else if ( *tidp == periodic[2] )
		printf("third_timer \n");
    else if( *tidp == oneshot1)
		printf("first one-shot \n");
    else if( *tidp== oneshot2)
		printf("second one-shot \n");
}

int
makeTimer(timer_t *timerID, int expireMS, int intervalMS, int mode )
{
    struct sigevent         te;
    struct itimerspec       its;
    struct sigaction        sa;
    int                     sigNo = SIGRTMIN;


    /* Set up signal handler. */
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = timerHandler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(sigNo, &sa, NULL) == -1)
    {
        printf("Failed to setup signal handling \n");
        return(-1);
    }

    /* Set and enable alarm */
    te.sigev_notify = SIGEV_SIGNAL;
    te.sigev_signo = sigNo;
    te.sigev_value.sival_ptr = timerID;
    timer_create(CLOCK_REALTIME, &te, timerID);

    if(mode==PERIODIC){
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = intervalMS * 1000000;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expireMS * 1000000;
    }
    if(mode==ONE_SHOT){
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;
    its.it_value.tv_sec = 0;
    its.it_value.tv_nsec = expireMS * 1000000;
    }

    timer_settime(*timerID, 0, &its, NULL); 
    
 
    return(0);
}

int main(int argc, char* argv[]){

	int rc;
        rc = makeTimer(&periodic[0], 60, 60, PERIODIC);
		rc = makeTimer(&periodic[1], 120, 120, PERIODIC);
		rc = makeTimer(&periodic[2], 180, 180, PERIODIC);
  		rc = makeTimer(&oneshot1, 240, 0, ONE_SHOT);
		rc = makeTimer(&oneshot2, 300, 0, ONE_SHOT);

	int i = 0;	
	printf("Entering main loop\n");		
	while(1){
		i++;
		sleep(1);
		if(i==60){
				// one option
				rc = makeTimer(&periodic[0], 0, 0, PERIODIC);
				rc = makeTimer(&periodic[1], 0, 0, PERIODIC);
				rc = makeTimer(&periodic[2], 0, 0, PERIODIC);
				// more 
				timer_delete(periodic[0]);
				timer_delete(periodic[1]);
				timer_delete(periodic[2]);
		printf("finished processing\n");		
		break;
		}
	}

return 0;
}
