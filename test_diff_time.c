#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

double
timeval_diff(struct timeval *difference,
             struct timeval *end_time,
             struct timeval *start_time
            )
{
  struct timeval temp_diff;

  if(difference==NULL)
  {
    difference=&temp_diff;
  }

  difference->tv_sec =end_time->tv_sec -start_time->tv_sec ;
  difference->tv_usec=end_time->tv_usec-start_time->tv_usec;

  /* Using while instead of if below makes the code slightly more robust. */

  while(difference->tv_usec<0)
  {
    difference->tv_usec+=1000000;
    difference->tv_sec -=1;
  }

  return ((double)(1000000*difference->tv_sec+
                   difference->tv_usec))/1000.0f;

} /* timeval_diff() */

int
main(void)
{
  struct timeval earlier;
  struct timeval later;
  struct timeval interval;

  /*
   * There are two ways to call timeval_diff.  The first way simply returns
   * the time difference as microseconds, a single integer.
   */

  if(gettimeofday(&earlier,NULL))
  {
    perror("first gettimeofday()");

    exit(1);
  }

  usleep(3000);

  if(gettimeofday(&later,NULL))
  {
    perror("second gettimeofday()");

    exit(1);
  }

  printf("difference is %lf milliseconds\n",
         timeval_diff(NULL,&later,&earlier)
        );


  return 0;

} /* main() */

