/* Orion Lawlor's Short UNIX Examples, olawlor@acm.org 2004/3/5

Shows how to use setitimer to get periodic interrupts,
and how to extract the program counter from a signal handler.
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#ifdef SOLARIS /* needed with at least Solaris 8 */
#include <siginfo.h>
#endif

void printStack(const char *where) {
	printf("%s stack: %p\n",where,&where);
}


#define __USE_GNU 1 /* required to get REG_EIP from glibc's ucontext.h */
#include <ucontext.h>

void *pcFromContext(ucontext_t *ctx) {

#if 0
#elif defined(REG_PC)
#  define PC_FROM_GREGS   REG_PC   /* generic; sun */

#elif defined(REG_EIP)
#  define PC_FROM_GREGS   REG_EIP  /* linux x86 (WORKS) */

#elif defined(EIP)
#  define PC_FROM_GREGS   EIP   /* old linux, solaris x86 */

#elif defined(__ia64__)
	return (void *)ctx->uc_mcontext.sc_ip; /* linux ia-64 (WORKS) */

#elif defined (__FreeBSD__)
	return (void *)ctx->uc_mcontext.mc_eip;
	
#elif defined (__NetBSD__)
	return (void *)ctx->sc_eip;
	
#else /* can't trace stacks */
	return NULL;
#endif 

#ifdef PC_FROM_GREGS
	return (void *)ctx->uc_mcontext.gregs[PC_FROM_GREGS];
#endif
}

void signalHandler(int cause, siginfo_t *HowCome, void *ucontext) {
	printStack("signal handler");
	printf(" ip at %p\n",pcFromContext((ucontext_t *)ucontext));
}

int main(){ 
	int i;
	struct itimerval itimer;
	
/* Install our SIGPROF signal handler */
        struct sigaction sa;
	
        sa.sa_sigaction = signalHandler;
        sigemptyset( &sa.sa_mask );
        sa.sa_flags = SA_SIGINFO; /* we want a siginfo_t */
        if (sigaction (SIGPROF, &sa, 0)) {
		perror("sigaction");
		exit(1);
        }
	
	printStack("main routine");

/* Request SIGPROF */
	itimer.it_interval.tv_sec=0;
	itimer.it_interval.tv_usec=10*1000;
	itimer.it_value.tv_sec=0;
	itimer.it_value.tv_usec=10*1000;
	setitimer(ITIMER_PROF, &itimer, NULL); 
	
/* Just wait a bit, which should get a few SIGPROFs */
	for (i=0;i<1000*1000*10;i++) {
	}

        return(0);
}
/*<@>
<@> ******** Program output: ********
<@> main routine stack: 0x7fffee73e0e0
<@> */
