#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>

bool running = true;

struct thread_data {
	int sockfd;
	struct sockaddr_in host;
};


void
diep(const char *e) {
	perror(e);
	exit(EXIT_FAILURE);
}


#define BUFFER_SIZE (1 << 12)
#define OUTPUT_DATA false

void*
recv_thread(void *ptr) {
	struct thread_data *td = (struct thread_data*)ptr;

	printf("recv: port %d\n", ntohs(td->host.sin_port));

	size_t nbytes = 0;
	char buf[BUFFER_SIZE];
	memset(buf, 0, BUFFER_SIZE);
	while (running) {
		int r = recv(td->sockfd, buf, BUFFER_SIZE, MSG_DONTWAIT);
		if (r == -1) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue;
			perror("recv");
			break;
		}
		else {
#if OUTPUT_DATA
			printf("recv: %s", buf);
			if (buf[strlen(buf)-1] != '\n')
				printf("\n");
			fflush(stdout);
#endif
			nbytes += (size_t)r;
		}
	}
	printf("%lu bytes received\n", nbytes);
	return NULL;
}

void
sighandler(int sig) {
	if (sig == SIGINT) {
		running = false;
	}
}

int
main() {
	signal(SIGINT, sighandler);


	/*
	 * build local addr and bind socket
	 */
	int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd == -1)
		diep("socket");

	struct sockaddr_in host;
	socklen_t host_len = sizeof(host);
	host.sin_family = AF_INET;
	host.sin_port   = htons(56010);
	host.sin_addr.s_addr   = htons(INADDR_ANY);

	if (bind(sockfd, (struct sockaddr*)&host, host_len) == -1)
		diep("bind");

	/*
	 * build remote socket and connect
	 */
	struct sockaddr_in peer;
	socklen_t peer_len = sizeof(peer);
	peer.sin_family = AF_INET;
	peer.sin_port   = htons(56010);
	if (inet_pton(AF_INET, "192.168.201.10", &peer.sin_addr) != 1)
		diep("inet_pton");
	if (connect(sockfd, (struct sockaddr*)&peer, peer_len) != 0)
		diep("connect");


	/*
	 * generate thread for receiving
	 */
	struct thread_data *td = malloc(sizeof(*td));
	memset(td, 0, sizeof(*td));
	memcpy(&td->host, &host, sizeof(host));
	td->sockfd = sockfd;

	pthread_t recv_t;
	if (pthread_create(&recv_t, NULL, recv_thread, td) != 0)
		diep("pthread_create");

	/*
	 * send some commands to start event stream
	 */
	// const char *event_mode = "!E31\n";
	const char *event_mode = "!E1\n";
	send(sockfd, event_mode, strlen(event_mode), 0);
	printf("send: event mode\n");

	const char *event_start = "E+\n";
	send(sockfd, event_start, strlen(event_start), 0);
	printf("send: event start\n");

	sleep(2);

	/*
	 * stop everything, reset eDVS (this does NOT work always!)
	 */
	running = false;
	const char *event_stop = "E-\nR\n";
	send(sockfd, event_stop, strlen(event_stop), 0);
	printf("send: event stop\n");

	pthread_join(recv_t, NULL);
}
