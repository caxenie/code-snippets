#include <stdio.h>
#include "highgui.h"
#include "cv.h"
#include <time.h>

double compute_dt(struct timespec *end_time, struct timespec *start_time){
  /* difference holder */
  struct timespec difference;
  /* compute difference */
  difference.tv_sec =end_time->tv_sec -start_time->tv_sec ;
  difference.tv_nsec=end_time->tv_nsec-start_time->tv_nsec;
  
  while(difference.tv_nsec<0)
  {
    difference.tv_nsec+=1000000000;
    difference.tv_sec -=1;
  }

  return ((double)(1000.0*(double)difference.tv_sec+
                   (double)difference.tv_nsec/1000000.0)); /* ms */

}

/* entry point */
int main(int argc, char* argv[])
{
	CvCapture *c = cvCreateFileCapture("http://10.162.242.18/mjpg/video.mjpg");
	IplImage* image = NULL;
	cvNamedWindow("IP Cam FPS", CV_WINDOW_AUTOSIZE);
	struct timespec tstart, tcur;	
	while(1) {
	if(clock_gettime(CLOCK_REALTIME, &tstart)==-1){
		printf("present_data: Cannot access time subsystem.");
	}
		image = cvQueryFrame(c);
		cvShowImage("IP Cam FPS", image);
		if(clock_gettime(CLOCK_REALTIME, &tcur)==-1){
			printf("present_data: Cannot access time subsystem.");
		}	
		printf("Diff: %lf\n", compute_dt(&tcur, &tstart));
		if((int)cvWaitKey(5) == 'q') break; /* check if q is sent */
	}


	return EXIT_SUCCESS;

}
