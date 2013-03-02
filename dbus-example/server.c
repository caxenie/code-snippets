
#include <dbus/dbus.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define SERVER_BUS_NAME 			"org.fusionmaps.network"
#define SERVER_SIGNAL_INTERFACE 	"org.fusionmaps.signals"
#define SERVER_METHOD_INTERFACE    "org.fusionmaps.methods"

#define METHOD1 "update_values"
#define SIGNAL1 "sensor_data_connected" 
#define SIGNAL2 "update_sensor_rate_changed"
#define SIGNAL3 "user_data_connected"
#define SIGNAL4 "update_user_data_changed"


double map1_val = 0.0, map2_val = 0.0, map3_val = 0.0, map4_val = 0.0, map5_val = 0.0, map6_val = 0.0, 
		map1_r1val = 0.0f, map2_r1val = 0.0f, map2_r2val = 0.0f, map3_r2val = 0.0f, map4_r2val =0.0, map4_r3val = 0.0f,
		map5_r3val = 0.0f, map6_r3val = 0.0f;


DBusConnection* conn;
DBusError err;

double rx_data[2];

void init_system_bus_connection(){
	int ret;
   // initialise the errors
   dbus_error_init(&err);
   
   // connect to the bus and check for errors
   conn = dbus_bus_get(DBUS_BUS_SYSTEM, &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stdout, "Connection Error (%s)\n", err.message);
      dbus_error_free(&err); 
   }
   if (NULL == conn) { 
      exit(1);
   }
   
   // request our name on the bus and check for errors
   ret = dbus_bus_request_name(conn, 
							   SERVER_BUS_NAME, 
							   DBUS_NAME_FLAG_REPLACE_EXISTING , 
							   &err);
   if (dbus_error_is_set(&err)) { 
      fprintf(stdout, "Name Error (%s)\n", err.message);
      dbus_error_free(&err); 
   }
   if (DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER != ret) {
      exit(1);
   }

	   // add a rule for which messages we want to see
   dbus_bus_add_match(conn, "type='signal',interface='org.fusionmaps.signals'", &err); // see signals from the given interface
   dbus_connection_flush(conn);
   if (dbus_error_is_set(&err)) { 
      fprintf(stdout, "Match Error (%s)\n", err.message);
      exit(1); 
   }

}


void handle_methods(DBusMessage *msg)
{
   DBusMessage* reply;
   DBusMessageIter args;

   dbus_uint32_t serial = 0;
   char* param = "";

   // read the arguments
   if (!dbus_message_iter_init(msg, &args))
      fprintf(stdout, "Message has no arguments!\n"); 
   else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args)) 
      fprintf(stdout, "Argument is not string!\n"); 
   else 
      dbus_message_iter_get_basic(&args, &param);

   printf("Method called with %s\n", param);

   // create a reply from the message
   reply = dbus_message_new_method_return(msg);

   // add the arguments to the reply
   dbus_message_iter_init_append(reply, &args);
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map1_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }
   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map3_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map5_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map6_val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map1_r1val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_r1val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map2_r2val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map3_r2val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_r2val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map4_r3val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map5_r3val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   if (!dbus_message_iter_append_basic(&args, DBUS_TYPE_DOUBLE, &map6_r3val)) { 
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }

   // send the reply && flush the connection
   if (!dbus_connection_send(conn, reply, &serial)) {
      fprintf(stdout, "Out Of Memory!\n"); 
      exit(1);
   }
   dbus_connection_flush(conn);

   // free the reply
   dbus_message_unref(reply);
}

/**
 * Listens for signals on the bus
 */
void handle_signals(DBusMessage *msg)
{
   DBusMessageIter args;
   char *sigvalue;
   double data;
   int map_id;
	           
         // read the parameters
	   if (!dbus_message_iter_init(msg, &args))
		  fprintf(stderr, "Message has no arguments!\n"); 
	   else if (DBUS_TYPE_STRING != dbus_message_iter_get_arg_type(&args)) 
		  fprintf(stderr, "Argument is not string!\n"); 
	   else
		  dbus_message_iter_get_basic(&args, &sigvalue);

	   if (!dbus_message_iter_next(&args))
		  fprintf(stderr, "Message has too few arguments!\n"); 
	   else if (DBUS_TYPE_DOUBLE != dbus_message_iter_get_arg_type(&args)) 
		  fprintf(stderr, "Argument is not double!\n"); 
	   else
		  dbus_message_iter_get_basic(&args, &data);

	   if (!dbus_message_iter_next(&args))
		  fprintf(stderr, "Message has too few arguments!\n"); 
	   else if (DBUS_TYPE_INT32 != dbus_message_iter_get_arg_type(&args)) 
		  fprintf(stderr, "Argument is not double!\n"); 
	   else
		  dbus_message_iter_get_basic(&args, &map_id);


	   printf("Got Signal %s with value %lf\n", sigvalue, data);

	         // perform some dummy processing depending on the signal type that was captured
		  if(dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL2)){
		  if(data<3){
				switch(map_id){
					case 1: 
							map1_r1val += data;
					break;
					case 2:
							map2_r1val += data;
					   	    map2_r2val += data;
					break;
					case 3:
							map3_r2val += data;
					break;
			   		case 4:
							map4_r2val += data;
						    map4_r3val += data;
					break;
					case 5:
						   map5_r3val += data;
					break;
					case 6:
						   map6_r3val += data;
					break;
					default:
					break;
			   }
		   }else{
				switch(map_id){
					case 1: 
							map1_r1val -= data;
					break;
					case 2:
							map2_r1val -= data;
					   	    map2_r2val -= data;
					break;
					case 3:
							map3_r2val -= data;
					break;
			   		case 4:
							map4_r2val -= data;
						    map4_r3val -= data;
					break;
					case 5:
						   map5_r3val -= data;
					break;
					case 6:
						   map6_r3val -= data;
					break;
					default:
					break;
			   }
			   
				   }
				   

			}

		  if(dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL4)){

		  if(data>0){
				switch(map_id){
					case 1: 
							map1_val += data;
					break;
					case 2:
							map2_val += data;
					break;
					case 3:
							map3_val += data;
					break;
			   		case 4:
							map4_val += data;
					break;
					case 5:
						   map5_val += data;
					break;
					case 6:
						   map6_val += data;
					break;
					default:
					break;
			   }
		   }else{
				switch(map_id){
					case 1: 
							map1_val += data;
					break;
					case 2:
							map2_val += data;
					break;
					case 3:
							map3_val += data;
					break;
			   		case 4:
							map4_val += data;
					break;
					case 5:
						   map5_val += data;
					break;
					case 6:
						   map6_val += data;
					break;
					default:
					break;
			   }
			   
				   }
				   

			}
}

/**
 * Server that exposes a method call and waits for it to be called
 */
void listen_to_clients() 
{
   DBusMessage* msg;
   DBusMessage* reply;
   DBusMessageIter args;
   int ret;
   char* param;

   printf("Listening for method calls & signals\n");

   // loop, testing for new messages
   while (1) {
      // non blocking read of the next available message
      dbus_connection_read_write(conn, 0);
      msg = dbus_connection_pop_message(conn);

      // loop again if we haven't got a message
      if (NULL == msg) { 
         sleep(1); 
         continue; 
      }
      
      // check this is a method call for the right interface & method
      if (dbus_message_is_method_call(msg, SERVER_METHOD_INTERFACE, METHOD1)) 
         			handle_methods(msg);

      if (dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL1) ||
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL2) || 
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL3) ||
		  dbus_message_is_signal(msg, SERVER_SIGNAL_INTERFACE, SIGNAL4))

				 	handle_signals(msg);

      // free the message
      dbus_message_unref(msg);
   }
}



int main(int argc, char** argv)
{
	  init_system_bus_connection();
      listen_to_clients();

   return 0;
}
