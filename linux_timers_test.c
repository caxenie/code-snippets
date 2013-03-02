#include <stdlib.h>
       #include <unistd.h>
       #include <stdio.h>
       #include <signal.h>
       #include <time.h>

enum{
	ONE_SHOT,
	PERIODIC
};

timer_t firstTimerID, secondTimerID;
timer_t oneshot1, oneshot2;


void
timerHandler( int sig, siginfo_t *si, void *uc )
{
    timer_t *tidp;
    tidp = si->si_value.sival_ptr;

    if ( *tidp == firstTimerID )
        printf("first\n");
    else if ( *tidp == secondTimerID )
		printf("second\n");
    else if( *tidp == oneshot1)
		printf("first one shot\n");
    else if( *tidp== oneshot2)
		printf("second one -shot \n");
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
        rc = makeTimer(&firstTimerID, 40, 40, PERIODIC);
	rc = makeTimer(&secondTimerID, 120, 120, PERIODIC);
        rc = makeTimer(&oneshot1, 50, 0, ONE_SHOT);
	rc = makeTimer(&oneshot2, 130, 0, ONE_SHOT);

	while(1);

return 0;
}
