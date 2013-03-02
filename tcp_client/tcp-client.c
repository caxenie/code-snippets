#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for omnirob_socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for omnirob_sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 128  /* Size of receive buffer */
#define OMNIROB_IP "192.168.201.50"
#define OMNIROB_PORT 56000

    int omnirob_sock;                        /* omnirob_socket descriptor */
    struct sockaddr_in omnirob_sock_addr; /* Echo server address */
    char *cmd_string;                /* String to send to echo server */
    char recv_buff[RCVBUFSIZE];     /* Buffer for echo string */
    int recv_bytes ;  /* Bytes read in single recv()  */
                                    
int connect_to_omnirob(char* ip, int port)
{
	/* Create a reliable, stream omnirob_socket using TCP */
    if ((omnirob_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        printf("CORE: OMNIROB_IFACE: omnirob_socket creation failed\n");
		return -1;
	}
	/* Construct the server address structure */
    memset(&omnirob_sock_addr, 0, sizeof(omnirob_sock_addr));     /* Zero out structure */
    omnirob_sock_addr.sin_family      = AF_INET;             /* Internet address family */
    omnirob_sock_addr.sin_addr.s_addr = inet_addr(ip);   /* Server IP address */
    omnirob_sock_addr.sin_port        = htons(port); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(omnirob_sock, (struct sockaddr *) &omnirob_sock_addr, sizeof(omnirob_sock_addr)) < 0){
        printf("CORE: OMNIROB_IFACE: connection to robot failed\n");
		return -2;
	}
	return 0;
}

int read_omnirob_gyro()
{
	const char* cmd = "?Ig\n";
	/* Send the interogation command string to the robot */
    if (send(omnirob_sock, cmd, strlen(cmd), 0) != strlen(cmd)){
        printf("CORE: OMNIROB_IFACE: send failed sent a different number of bytes than expected\n");
		return -1;
	}
	/* Get the reply */
    if ((recv_bytes = recv(omnirob_sock, recv_buff, RCVBUFSIZE - 1, 0)) <= 0){
            printf("CORE: OMNIROB_IFACE: receive failed or connection closed prematurely\n");
			return -2;	
	}
    recv_buff[recv_bytes] = '\0';  /* Terminate the string! */
    printf("%s", recv_buff);      /* Print the echo buffer */
	
	return recv_bytes;
}


int read_omnirob_compass()
{
	const char* cmd = "?Ic\n";
		/* Send the interogation command string to the robot */
    if (send(omnirob_sock, cmd, strlen(cmd), 0) != strlen(cmd)){
        printf("CORE: OMNIROB_IFACE: send failed sent a different number of bytes than expected\n");
		return -1;
	}
	/* Get the reply */
    if ((recv_bytes = recv(omnirob_sock, recv_buff, RCVBUFSIZE - 1, 0)) <= 0){
            printf("CORE: OMNIROB_IFACE: receive failed or connection closed prematurely\n");
			return -2;	
	}
    recv_buff[recv_bytes] = '\0';  /* Terminate the string! */
    printf("%s", recv_buff);      /* Print the echo buffer */
	
	return recv_bytes;
}

int read_omnirob_wheels()
{
	const char* cmd = "?Wi\n"; // TODO check what do we need from here
		/* Send the interogation command string to the robot */
    if (send(omnirob_sock, cmd, strlen(cmd), 0) != strlen(cmd)){
        printf("CORE: OMNIROB_IFACE: send failed sent a different number of bytes than expected\n");
		return -1;
	}
	/* Get the reply */
    if ((recv_bytes = recv(omnirob_sock, recv_buff, RCVBUFSIZE - 1, 0)) <= 0){
            printf("CORE: OMNIROB_IFACE: receive failed or connection closed prematurely\n");
			return -2;	
	}
    recv_buff[recv_bytes] = '\0';  /* Terminate the string! */
    printf("%s", recv_buff);      /* Print the echo buffer */
	
	return recv_bytes;
}



int disconnect_from_omnirob()
{
	if(omnirob_sock!=0) close(omnirob_sock);
}


int main(int argc, char *argv[])
{
	connect_to_omnirob(OMNIROB_IP, OMNIROB_PORT);
	read_omnirob_compass();
	read_omnirob_gyro();
	read_omnirob_wheels();
	disconnect_from_omnirob();
	   
    return 0;
}

