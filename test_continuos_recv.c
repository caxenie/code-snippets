#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#define OMNIROB_IP          "192.168.201.65"
#define COMM_PORT_OMNIROB   "56000"
#define MAXDATASIZE 8192

    // server info struct
    struct addrinfo hints, *servinfo;
    // address
    char *addr;
    // port
    char *port;
    // socket
    int s;
    // bytes read
    int numbytes;
    // event byte buffer
    char sensor_rx_buf[MAXDATASIZE];

void init_connection(char *_port, char * _addr)
{
	int res;
    port = _port;
    addr = _addr;
    //setup the socket
    memset(&hints, 0, sizeof hints);    // make sure the struct is empty
    hints.ai_family = AF_UNSPEC;        // don't care IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM;    // TCP stream sockets
    //setup the address struct
    if ((res = getaddrinfo(addr,port,&hints,&servinfo)) != 0)
    {
		printf("Error getting addresss infor !\n");
        exit(-1);
    }
    //setup the socket
    if ((s = socket(servinfo->ai_family,servinfo->ai_socktype,servinfo->ai_protocol)) == -1)
    {
        printf("ROBOT IFACE: SENSORS_COMM: Error creating socket! \n");
        exit(-1);
    }

	// connect to sensor
    if (connect(s,servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        close (s);
        printf("ROBOT IFACE: SENSORS_COMM: Error connecting to sensor!\n");
        exit(-1);
    }

    // free some unneeded memory
    freeaddrinfo(servinfo);
}

int send_cmd(char *msg)
{
    int len = strlen(msg);
    int bytes_sent = send(s,msg,len,0);

    if (bytes_sent <= 0)
        return -1;
    else
        return 0;
}

int main(int argc, char*argv[])
{
	char* sensor_rx_buf_proc;
	init_connection(COMM_PORT_OMNIROB, OMNIROB_IP);

  // send command to start sensor data stream from the robot @ 20Hz
    if (send_cmd((char*)"!I1,77,A\n") == -1){
        close(s);
        printf("ROBOT IFACE: SENSORS_COMM: Error sending start stream command!\n");
    }

    //Recv reply
    numbytes = recv(s,sensor_rx_buf,200,0);
    if (numbytes == -1){
        close(s);
        printf("ROBOT IFACE: SENSORS_COMM: No data received from robot controller !\n");
        exit(-1);
    }

    // loop for data
    while(1) // 14ms --> 77Hz
    {
        // clean buffer
        bzero(sensor_rx_buf,MAXDATASIZE);

        //Recv data
        numbytes = recv(s,sensor_rx_buf,200,0);
        if (numbytes == -1){
            close(s);
            printf("ROBOT IFACE: SENSORS_COMM: No data received from robot!\n");
            exit(-1);
        }

        //break if connection closed
        if (numbytes==0)
        {
            printf("ROBOT IFACE: SENSORS_COMM: No data received. Closing connection!\n");
            break;
        }

        sensor_rx_buf[numbytes]='\0';
		sensor_rx_buf_proc = strtok(sensor_rx_buf,"\n");
		if(strstr(sensor_rx_buf_proc, "-Ig=")!=NULL && 
		   strstr(sensor_rx_buf_proc, "a=")!=NULL && 
		   strstr(sensor_rx_buf_proc, "e=")!=NULL && 
		   strstr(sensor_rx_buf_proc, "c=")!=NULL && 
		   strstr(sensor_rx_buf_proc, "b=")!=NULL &&
		   strstr(sensor_rx_buf_proc, "wv=")!=NULL)
				printf("RES: %s\n",sensor_rx_buf);
}

	return 0;
}


