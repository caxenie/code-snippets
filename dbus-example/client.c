#define DBUS_API_SUBJECT_TO_CHANGE
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER_BUS_NAME 			"org.fusionmaps.network"
#define CLIENT_BUS_NAME 			"org.fusionmaps.visualizer"
#define SERVER_SIGNAL_INTERFACE 	"org.fusionmaps.signals"
#define SERVER_METHOD_INTERFACE    	"org.fusionmaps.methods"
#define BUS_METHODS_OBJECT 			"/org/fusionmaps/methods/object"
#define BUS_SIGNALS_OBJECT 			"/org/fusionmaps/signals/object"

DBusConnection* conn;
DBusError err;

void init_bus_interface(){

	int ret;
	// initialise the error value
   dbus_error_init(&err);

   // connect to the DBUS system bus, and check for errors
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Connection Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
      exit(1); 
   }

   // register our name on the bus, and check for errors
   ret = dbus_bus_request_name(conn, CLIENT_BUS_NAME, DBUS_NAME_FLAG_REPLACE_EXISTING , &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stderr, "Name Error (%s)\n", err.message); 
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) { 
      exit(1);
   }

}

/**
 * Connect to the DBUS bus and send a broadcast signal
 */
void send_signal(double val, const char* sigvalue)
{
   DBusMessage* msg;
   DBusMessageIter args;

   dbus_uint32_t serial = 0;

   printf("Sending signal %s with value %lf\n", sigvalue, val);

   // create a signal & check for errors 
   msg = dbus_message_new_signal(BUS_SIGNALS_OBJECT, // object name of the signal
                                 SERVER_SIGNAL_INTERFACE, // interface name of the signal
                                 sigvalue); // name of the signal
   if (NULL == msg) 
   { 
      fprintf(stderr, "Message Null\n"); 
      exit(1); 
   }

   // append arguments onto signal
   dbus_message_iter_init_append(msg, &args);
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &sigvalue)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &val)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }

   // send the message and flush the connection
   if (!dbus_connection_send(conn, msg, &serial)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }
   dbus_connection_flush(conn);
   
   printf("Signal Sent\n");
   
   // free the message and close the connection
   dbus_message_unref(msg);
}

/**
 * Call a method on a remote object
 */
void send_method_call(const char* param) 
{
   DBusMessage* msg;
   DBusMessageIter args;
   DBusPendingCall* pending;
   int ret;
   double level;

   printf("Calling remote method with %s\n", param);

   // create a new method call and check for errors
   msg = dbus_message_new_method_call( SERVER_BUS_NAME , // target for the method call
                                       BUS_METHODS_OBJECT, // object to call on
                                       SERVER_METHOD_INTERFACE, // interface to call on
                                       param); // method name
   if (NULL == msg) { 
      fprintf(stderr, "Message Null\n");
      exit(1);
   }

   // append arguments
   dbus_message_iter_init_append(msg, &args);
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_STRING, &param)) {
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }
   
   // send message and get a handle for a reply
   if (!dbus_connection_send_with_reply (conn, msg, &pending, -1)) { // -1 is default timeout
      fprintf(stderr, "Out Of Memory!\n"); 
      exit(1);
   }
   if (NULL == pending) { 
      fprintf(stderr, "Pending Call Null\n"); 
      exit(1); 
   }
   dbus_connection_flush(conn);
   
   printf("Request Sent\n");
   
   // free message
   dbus_message_unref(msg);
   
   // block until we recieve a reply
   dbus_pending_call_block(pending);

   // get the reply message
   msg = dbus_pending_call_steal_reply(pending);
   if (NULL == msg) {
      fprintf(stderr, "Reply Null\n"); 
      exit(1); 
   }
   // free the pending message handle
   dbus_pending_call_unref(pending);

   printf("Got Reply: \n");

   // read the parameters
   if (!dbus_message_iter_init(msg, &args))
      fprintf(stderr, "Message has no arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);
  
   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);
  
   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);

   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);
  
   if (!dbus_message_iter_next(&args))
      fprintf(stderr, "Message has too few arguments!\n"); 
   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stderr, "Argument is not double!\n"); 
   else
      dbus_message_iter_get_basic(&args, &level);
	printf("%lf\n", level);
   
   // free reply and close connection
   dbus_message_unref(msg);   
}

int main(int argc, char** argv)
{
	  init_bus_interface();
      //send_signal( 12.00f, argv[2]);
    send_method_call( argv[1]);

   return 0;
}
