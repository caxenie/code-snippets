#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

struct timespec t1cur, t1ant, t2cur, t2ant;

if(clock_gettime(CLOCK_REALTIME, &t1cur)==-1){
	exit(EXIT_FAILURE);
}

t1ant.tv_nsec = t1cur.tv_nsec;
t1ant.tv_sec = t1cur.tv_sec;

if(clock_gettime(CLOCK_REALTIME, &t2cur)==-1){
        exit(EXIT_FAILURE);
}


t2ant.tv_nsec = t2cur.tv_nsec;
t2ant.tv_sec = t2cur.tv_sec;

printf("T1cur: %ld [s]| %ld [ns]\n", t1cur.tv_sec/1000000, t1cur.tv_nsec/1000000);
printf("T1ant: %ld [s]| %ld [ns]\n", t1ant.tv_sec/1000000, t1ant.tv_nsec/1000000);
printf("T2cur: %ld [s]| %ld [ns]\n", t2cur.tv_sec/1000000, t2cur.tv_nsec/1000000);
printf("T2ant: %ld [s]| %ld [ns]\n", t2ant.tv_sec/1000000, t2ant.tv_nsec/1000000);

int j = 10;

while(j>0){

	if(clock_gettime(CLOCK_REALTIME, &t1cur)==-1){
        exit(EXIT_FAILURE);
}


if(clock_gettime(CLOCK_REALTIME, &t2cur)==-1){
        exit(EXIT_FAILURE);
}




j--;

printf("iter %d\n", j);
printf("T1cur: %ld [s]| %ld [ns]\n", t1cur.tv_sec/1000000, t1cur.tv_nsec/1000000);
printf("T1ant: %ld [s]| %ld [ns]\n", t1ant.tv_sec/1000000, t1ant.tv_nsec/1000000);
printf("T2cur: %ld [s]| %ld [ns]\n", t2cur.tv_sec/1000000, t2cur.tv_nsec/1000000);
printf("T2ant: %ld [s]| %ld [ns]\n", t2ant.tv_sec/1000000, t2ant.tv_nsec/1000000);


t1ant.tv_nsec = t1cur.tv_nsec;
t1ant.tv_sec = t1cur.tv_sec;

t2cur.tv_nsec = t2ant.tv_nsec;
t2ant.tv_sec = t2ant.tv_sec;


}

return 0;

}
