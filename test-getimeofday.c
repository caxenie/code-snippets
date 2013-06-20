#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void)
{
  struct timeval interval;

  if(gettimeofday(&interval, NULL))
  {
    perror("second gettimeofday()");

    exit(1);
  }

  printf("timestamp is %lf milliseconds\n",
         (interval.tv_sec*1000000 + interval.tv_usec)/1000.0);

  return 0;

} /* main() */

