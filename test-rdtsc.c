/* rdtsc.c 
 *
 * Copyright (C) 2000 Nathan Laredo <laredo@gnu.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <inttypes.h>
#include <string.h>
#include <memory.h>

#define rdtsc() ({ uint64_t x; asm volatile("rdtsc" : "=A" (x)); x; })

static uint64_t start_tsc, now_tsc, delta_tsc, count;

static void timer(int n)
{
	uint64_t old_tsc = now_tsc, run_freq;

	now_tsc = rdtsc();
	if (count == 0) {
		start_tsc = now_tsc;
	}
	delta_tsc = now_tsc - old_tsc;
	if (count > 0) {
		run_freq = (now_tsc - start_tsc) / count;
		fprintf(stderr, "\r%20qd %20qd %20qd(%qd)",
			now_tsc, delta_tsc, run_freq, count);
	}
	count++;
}

int main(int argc, char **argv)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = timer;
	act.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &act, NULL);
	setitimer(ITIMER_REAL, &(const struct itimerval) { { 1, 0 }, { 1, 0} }, NULL);
	while (1) {
		sleep(5);
	}
}
