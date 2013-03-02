CC=gcc
CFLAGS=-g -O2
PKGFLAGS=`pkg-config --cflags --libs dbus-1`

all:
	echo "\n Compiling low level API DBus demo...\n"
	$(CC) -o client client.c $(CFLAGS) $(PKGFLAGS)
	$(CC) -o server server.c $(CFLAGS) $(PKGFLAGS)
	echo "\n Done! \n"
clean:
	rm client server
