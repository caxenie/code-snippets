#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ucontext.h>

/* How to access the PC from a struct ucontext */
#ifndef REG_EIP
#define REG_EIP 0x00a01004L
#endif


void signal_handler (int signo, siginfo_t *si, void *data) {
        ucontext_t *uc;
        uc = (ucontext_t *) data;

        switch (signo) {
                case SIGFPE:
                        fprintf(stdout, "Caught FPE\n");
                        uc->uc_mcontext.gregs[REG_EIP]++;
                        printf("here\n");
			break;
                default:
                        fprintf(stdout, "default handler\n");
        }
}

int main (void) {
        struct sigaction sa, osa;
        unsigned int b = ULONG_MAX;

        sa.sa_flags = SA_ONSTACK | SA_RESTART | SA_SIGINFO;
        sa.sa_sigaction = signal_handler;
        sigaction(SIGFPE, &sa, &osa);

        b /= 0x0;

        return 0;
}

