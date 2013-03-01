#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

struct foo
{
	timer_t timer;
	char *str;
};

static void foo_timer(union sigval sival)
{
	struct foo *f;

	f = sival.sival_ptr;
	puts (f->str);
}

struct foo *foo_start(const char *str, unsigned sec)
{
	struct foo *f;
	struct sigevent ev;
	struct itimerspec it;

	f = malloc(sizeof (*f));
	f->str = strdup(str);

	memset(&ev, 0, sizeof (ev));
	ev.sigev_notify = SIGEV_THREAD;
	ev.sigev_value.sival_ptr = f;
	ev.sigev_notify_function = foo_timer;
	ev.sigev_notify_attributes = NULL;
	timer_create(CLOCK_MONOTONIC, &ev, &f->timer);

	it.it_interval.tv_sec = sec;
	it.it_interval.tv_nsec = 0;
	it.it_value.tv_sec = 0;
	it.it_value.tv_nsec = 1;
	timer_settime(f->timer, 0, &it, NULL);

	return f;
}

void foo_stop(struct foo *f)
{
	timer_delete(f->timer);
	free(f->str);
	free(f);
}

/* --- Main program --- */
#include <unistd.h>

int main (int argc, const char *argv[])
{
	struct foo *f;

	f = foo_start ("Hello world!", 1);
	getc (stdin);
	foo_stop (f);
	return 0;
}
