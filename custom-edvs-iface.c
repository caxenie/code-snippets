/* simple application to set a custom baudrate to a serial port in Linux */

#include <termio.h>
#include <fcntl.h>
#include <err.h>
#include <linux/serial.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define PORT "/dev/ttyUSB0"     // check the correct port identifier, run in the command line: dmesg | tail and look for /dev/ttyUSBxx 
#define RATE 12000000             // desired baudrate

/* open serial port in raw mode, with custom baudrate */
int serial_port_init(const char *port, int baudrate)
{
    struct termios options;
    struct serial_struct ser;
    int temp, flags;
    int fd;
    
    if((fd = open(port, O_RDWR))==-1){    // open port
        printf("ERROR - Unable to open \"%s\"\n",port);
        return -1;
    }
    
    ioctl(fd, TIOCGSERIAL, &ser);                               // get the current port options
    printf("Baud_base = %d\n",ser.baud_base);          // check the base baud rate provided by system
    ser.flags |= ASYNC_SPD_CUST;                           // activate custom speed option
    ser.flags |= ASYNC_LOW_LATENCY;                   // activate low latency option
    ser.custom_divisor = ser.baud_base / baudrate;   // compute the divisor to apply to base baudrate
    printf("custom_divisor = %d\n",ser.custom_divisor);
    printf("closest baud rate = %d\n",ser.baud_base/ser.custom_divisor);
    ioctl(fd, TIOCSSERIAL, &ser);                                // set the options
  
    
    flags = B38400;                                           // default flags
    tcgetattr(fd,&options);                                                 //get current options from port
    cfsetispeed(&options, flags);                       //set input baud rate
    cfsetospeed(&options, flags);                      //set output baud rate
    options.c_cflag = (options.c_cflag & ~CSIZE) | CS8;  //transmission size to 8bit
    options.c_cflag |= (CLOCAL | CREAD);                      //enable receiver and set local mode
    options.c_cflag |= CRTSCTS;                                     //use hardware handshaking (RTS/CTS)
    options.c_iflag = IGNBRK;                                          //clear input options: Send a SIGINT when a break condition is detected
    options.c_lflag = 0;                                                      //clear local options
    options.c_oflag = 0;                                                     //clear output options
    options.c_cc[VMIN] = 1;                                              //set minimum character count to receive to 1 
    options.c_cc[VTIME] = 5;                                            //set inter character timeout to 500 ms
    tcsetattr(fd,TCSANOW,&options);                               //set new options to port
    tcflush(fd,TCIFLUSH);                                                 //flush input buffer
  return fd;
}

int main(int argc, char*argv){
	int fd, wnbytes, rnbytes;
	char buffer[2200];
        char *bufptr;
        
	// open and configure port
	if((fd=serial_port_init(PORT, RATE))<0){
		printf("Cannot open port and set port attributes\n");
	}

	// test port send "??" and wait for the reply - eDVS CLI menu
	printf("--------------------------------\n");
	printf("WRITE: \n ??\n");
	wnbytes = write(fd, "??\n", 3);
	if (wnbytes < 0)
	  printf("write() failed!\n");

	 // read characters into our string buffer
    	bufptr = buffer;
    	while ((rnbytes = read(fd, bufptr, buffer + sizeof(buffer) - bufptr - 1)) > 0){
	      bufptr += rnbytes;
       }
       
       // nul terminate the string and print it
      *bufptr = '\0';
       printf("--------------------------------\n");
       printf("READ: \n %s\n", buffer);
       
      return EXIT_SUCCESS;
}

