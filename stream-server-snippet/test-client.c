/* 
 * A simple TCP client to be used to capture data from the robot tracker application.
 * The server stream out data using the format: XPOS,YPOS,HEADING,ITER,TIMESTAMP
 * usage: tcpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 10

/* buffer to store incoming data */
char buf[BUFSIZE];
/* socket fd */
int sockfd;

/* initialize the connection to the server */
int init_client(char *hostname, int portno){

    /* server vars */
    struct sockaddr_in serveraddr;
    struct hostent *server;

    /* create the socket */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0) {
        printf("ERROR opening socket!\n");
	return -1;
    }

    /* get the server's DNS entry */
    if ((server = gethostbyname(hostname)) == NULL) {
        printf("ERROR, no such server %s!\n", hostname);
	return -2;
    }

    /* build the server's structs */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* connect: create a connection with the server */
    if (connect(sockfd,(struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
      printf("ERROR connecting!\n");
      return -3;
    }
    return 0;
}

int main(int argc, char **argv) {
    
     /* number of bytes read */
     int numbytes = 0;

    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(EXIT_SUCCESS);
    }
 
    /* initialize client connection */
    if(init_client(argv[1], atoi(argv[2]))!=0){
	printf("Exiting.\n");
	goto out;
    }
 
    /* print the server stream */
    while(1){ 
	/* clean the buffer */
    	bzero(buf, BUFSIZE);
	/* read from socket */
	if((numbytes = read(sockfd, buf, BUFSIZE))<0){
	      printf("ERROR reading from socket\n");
	      goto out;
	}
     /* for proper printing*/
     buf[BUFSIZE]='\0';
     printf("%s", buf);
    }

out:
	close(sockfd);
	return (EXIT_SUCCESS);
}
