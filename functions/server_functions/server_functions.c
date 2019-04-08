#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "structures.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "file_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "network_wallet_functions.h"
#include "server_functions.h"
#include "string_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_current_consensus_nodes_IP_address
Description: Gets the current consensus nodes IP address, so the node knows which consensus node to send and receive data from
Parameters:
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_current_consensus_nodes_IP_address()
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; \
  free(message); \
  message = NULL; \
  free(message2); \
  message2 = NULL;

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL || data2 == NULL || message == NULL || message2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (message2 != NULL)
    {
      pointer_reset(message2);
    }
    return 0;
  }

  // create the message
  memcpy(message,"{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS\",\r\n}",102);

  // sign_data
  if (sign_data(message,0) == 0)
  { 
    color_print("Could not sign_data","red");
    pointer_reset_all;
    return 0;
  }
 
  // send the message to the consensus node and consensus backup node
  const int SEND_AND_RECEIVE_DATA_SOCKET_DATA1 = send_and_receive_data_socket(data,CONSENSUS_NODES_IP_ADDRESS,SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",0);
  const int SEND_AND_RECEIVE_DATA_SOCKET_DATA2 = send_and_receive_data_socket(data2,CONSENSUS_BACKUP_NODES_IP_ADDRESS,SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"NODE_TO_CONSENSUS_NODE_SEND_CURRENT_CONSENSUS_NODE_IP_ADDRESS",0);

  // verify the data
  if (verify_data(data,0,1,1) == 0 || verify_data(data2,0,1,1) == 0)
  {   
    color_print("Could not verify data from the consensus node","red");
    pointer_reset_all;
    return 0; 
  }

  // parse the data
  memset(message,0,strnlen(message,BUFFER_SIZE));
  if (parse_json_data(data,"current_consensus_node_IP_address",message) == 0 || parse_json_data(data2,"current_consensus_node_IP_address",message2) == 0)
  {
    color_print("Could not parse current_consensus_node_IP_address from the CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS message","red");
    pointer_reset_all;
    return 0; 
  }
  
  // check what consensus node IP address is the current consensus node IP address
  if (SEND_AND_RECEIVE_DATA_SOCKET_DATA1 == 1 && SEND_AND_RECEIVE_DATA_SOCKET_DATA2 == 1 && strncmp(message,message2,BUFFER_SIZE) != 0)
  {
    // The consensus node and the consensus backup node returned different results
    color_print("The consensus node and the consensus backup node returned different results\n","red");
    pointer_reset_all;
    return 0;
  }
  else if (SEND_AND_RECEIVE_DATA_SOCKET_DATA1 == 1 && SEND_AND_RECEIVE_DATA_SOCKET_DATA2 == 1 && strncmp(message,message2,BUFFER_SIZE) == 0)
  {
    memcpy(current_consensus_nodes_IP_address,message,strnlen(message,BUFFER_SIZE));    
  }
  else if (SEND_AND_RECEIVE_DATA_SOCKET_DATA1 == 1 && SEND_AND_RECEIVE_DATA_SOCKET_DATA2 == 0)
  {
    memcpy(current_consensus_nodes_IP_address,message,strnlen(message,BUFFER_SIZE));  
  }
  else if (SEND_AND_RECEIVE_DATA_SOCKET_DATA1 == 0 && SEND_AND_RECEIVE_DATA_SOCKET_DATA2 == 1)
  {
    memcpy(current_consensus_nodes_IP_address,message2,strnlen(message2,BUFFER_SIZE));  
  }
  else
  {
    color_print("An error has occured\n","red");
    pointer_reset_all;
    return 0; 
  }
  return 1;

  #undef pointer_reset_all
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_received_data_xcash_proof_of_stake_test_data
Description: Runs the code when the server receives the xcash_proof_of_stake_test_data message
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_received_data_xcash_proof_of_stake_test_data(const int CLIENT_SOCKET, char* MESSAGE)
{
  // verify the message
  if (verify_data(MESSAGE,0,1,1) == 0)
  {   
    return 0;
  }
  else
  {
    if (send_data(CLIENT_SOCKET,MESSAGE,1) == 1)
    {
      return 1;
    }
    else
    {
      return 0;
    }
  }  
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_received_data_xcash_proof_of_stake_test_data
Description: Runs the code when the server receives the CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS message. This function will read the settings from the text file and send it to the consensus node. The text file will be changed manually if the blockchain needs to go on an auto mode. If the settings are 1 it is on the auto mode, and if the settings are 0 it is not on the auto mode.
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_set_xcash_proof_of_stake_settings(const int CLIENT_SOCKET, char* MESSAGE)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate all of the variables on the heap\nFunction: server_receive_data_set_xcash_proof_of_stake_settings\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red"); 
    return 0;
  }

  // define macros
  #define XCASH_PROOF_OF_STAKE_SETTINGS_FILE "xcash_proof_of_stake_settings.txt"
  #define MESSAGE1 "{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_settings\": \"0\",\r\n}"
  #define MESSAGE2 "{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_settings\": \"1\",\r\n}"

  // verify the message
  if (verify_data(MESSAGE,0,0,0) == 0)
  {  
    color_print("Could not verify the message from the consensus node\nFunction: server_receive_data_set_xcash_proof_of_stake_settings\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red"); 
    return 0;
  }

  // read the settings from the text file
  if (read_file(data, XCASH_PROOF_OF_STAKE_SETTINGS_FILE) == 0)
  {
    color_print("Could not read the xcash_proof_of_stake_settings.txt file\nFunction: server_receive_data_set_xcash_proof_of_stake_settings\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red"); 
    return 0;
  }

  // create the message
  memset(data,0,strnlen(data,BUFFER_SIZE));
  if (memcmp(data,"0",1) == 0)
  {
    memcpy(data,MESSAGE1,144);
  }
  else
  {
    memcpy(data,MESSAGE2,144);
  } 

  // sign the message
  if (sign_data(data,0) == 0)
  { 
    color_print("Could not sign the message\nFunction: server_receive_data_set_xcash_proof_of_stake_settings\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red"); 
  } 

  if (send_data(CLIENT_SOCKET,data,strnlen(data,BUFFER_SIZE)) == 0)
  {
    color_print("Could not send the data to the consensus node\nFunction: server_receive_data_set_xcash_proof_of_stake_settings\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red"); 
    return 0;
  }

  return 1;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_block_producer_create_block
Description: Runs the code when the server receives the CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK message. This function will sign the block_blob that the block producer created, that the consensus node sent over. This way the block is valid to be added to the network.
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_block_producer_create_block(const int CLIENT_SOCKET, char* MESSAGE)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    return 0;
  }

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate all of the variables on the heap\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
    return 0;
  }

  // verify the message
  if (verify_data(MESSAGE,0,0,0) == 0)
  {  
    color_print("Could not verify the message from the consensus node\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // parse the message
  if (parse_json_data(MESSAGE,"block_blob",data) == 0)
  {
    color_print("Could not parse the message from the consensus node\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // sign the block_blob
  if (sign_block_data(data, 0) == 0)
  {
    color_print("Could not sign the block_blob\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // create the message
  const size_t DATA_LENGTH = strnlen(data,BUFFER_SIZE);
  memcpy(data2,"{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"", 101);
  memcpy(data2+101,data,DATA_LENGTH);
  memcpy(data2+101+DATA_LENGTH,"\",\r\n}",5);
  
  // sign the message
  if (sign_data(data,0) == 0)
  { 
    color_print("Could not sign the message\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
  } 

  if (send_data(CLIENT_SOCKET,data,strnlen(data,BUFFER_SIZE)) == 0)
  {
    color_print("Could not send the data to the consensus node\nFunction: server_receive_data_block_producer_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
    return 0;
  }
  
  return 1;
}



/*
-----------------------------------------------------------------------------------------------------------
Name: server_receive_data_consensus_node_create_block
Description: Runs the code when the server receives the CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK message. This function will sign the block_blob that the block producer created, that the consensus node sent over. This way the block is valid to be added to the network.
Parameters:
  CLIENT_SOCKET - The socket to send data to
  message - The message
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int server_receive_data_consensus_node_create_block(const int CLIENT_SOCKET, char* MESSAGE)
{
  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data2 = (char*)calloc(BUFFER_SIZE,sizeof(char));

  if (data == NULL || data2 == NULL)
  {
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (data2 != NULL)
    {
      pointer_reset(data2);
    }
    return 0;
  }

  // check if the memory needed was allocated on the heap successfully
  if (data == NULL)
  {
    color_print("Could not allocate all of the variables on the heap\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
    return 0;
  }

  // verify the message
  if (verify_data(MESSAGE,0,0,0) == 0)
  {  
    color_print("Could not verify the message from the consensus node\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // parse the message
  if (parse_json_data(MESSAGE,"block_blob",data) == 0)
  {
    color_print("Could not parse the message from the consensus node\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // sign the block_blob
  if (sign_block_data(data, 0) == 0)
  {
    color_print("Could not sign the block_blob\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");  
    return 0;
  }

  // create the message
  const size_t DATA_LENGTH = strnlen(data,BUFFER_SIZE);
  memcpy(data2,"{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"", 101);
  memcpy(data2+101,data,DATA_LENGTH);
  memcpy(data2+101+DATA_LENGTH,"\",\r\n}",5);
  
  // sign the message
  if (sign_data(data,0) == 0)
  { 
    color_print("Could not sign the message\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
  } 

  if (send_data(CLIENT_SOCKET,data,strnlen(data,BUFFER_SIZE)) == 0)
  {
    color_print("Could not send the data to the consensus node\nFunction: server_receive_data_consensus_node_create_block\nReceived Message: CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\nSend Message: BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red"); 
    return 0;
  }
  
  return 1;
}




/*
-----------------------------------------------------------------------------------------------------------
Name: create_server
Description: Creates the server
Parameters:
   MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int create_server(const int MESSAGE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"};   
  const int SOCKET_OPTION = 1;  
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char buffer[BUFFER_SIZE];
  char buffer2[BUFFER_SIZE];
  char client_address[BUFFER_SIZE];  
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char)); 
  int len;
  int receive_data_result; 
  struct sockaddr_in addr, cl_addr;  
  struct sockaddr_in serv_addr;

  // define macros
  #define SOCKET_FILE_DESCRIPTORS_LENGTH 1
  #define pointer_reset_all \
  free(string); \
  string = NULL;

  // threads
  pthread_t thread_id;

  // set the main process to ignore if forked processes return a value or not, since the timeout for the total connection time is run on a different thread
  signal(SIGCHLD, SIG_IGN);  

  // check if the memory needed was allocated on the heap successfully
  if (string == NULL)
  {
    return 0;
  }
    
  /* Create the socket  
  AF_INET = IPV4 support
  SOCK_STREAM = TCP protocol
  */
  const int SOCKET = socket(AF_INET, SOCK_STREAM, 0);
  if (SOCKET == -1)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error creating socket","red");
    }    
    pointer_reset_all;
    return 0;
  }

  /* Set the socket options
  SOL_SOCKET = socket level
  SO_REUSEADDR = allows for reuse of the same address, so one can shutdown and restart the program without errros
  SO_REUSEPORT = allows for reuse of the same port, so one can shutdown and restart the program without errros
  */
  if (setsockopt(SOCKET, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &SOCKET_OPTION,sizeof(int)) != 0)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error setting socket options","red"); 
    }
    close(SOCKET);
    pointer_reset_all;
    return 0;
  } 
  if (MESSAGE_SETTINGS == 1)
  {
    color_print("Socket created","green");
  }
 
  // convert the port to a string
  sprintf(buffer2,"%d",SEND_DATA_PORT);  
 
  memset(&addr, 0, sizeof(addr));
  /* setup the connection
  AF_INET = IPV4
  INADDR_ANY = connect to 0.0.0.0
  use htons to convert the port from host byte order to network byte order short
  */
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_port = htons(SEND_DATA_PORT);
 
  // connect to 0.0.0.0
  if (bind(SOCKET, (struct sockaddr *) &addr, sizeof(addr)) != 0)
  {
   if (MESSAGE_SETTINGS == 1)
   {
     memset(string,0,strnlen(string,BUFFER_SIZE));
     memcpy(string,"Error connecting to port ",25);
     memcpy(string+25,buffer2,strnlen(buffer2,BUFFER_SIZE));
     color_print(string,"red"); 
   }
   close(SOCKET);
   pointer_reset_all;
   return 0;
  } 
  if (MESSAGE_SETTINGS == 1)
  {
    memset(string,0,strnlen(string,BUFFER_SIZE));
    memcpy(string,"Connected to port ",18);
    memcpy(string+18,buffer2,strnlen(buffer2,BUFFER_SIZE));
    color_print(string,"green");

    printf("Waiting for a connection...\n");
  }

  // set the maximum simultaneous connections
  if (listen(SOCKET, MAXIMUM_CONNECTIONS) != 0)
  {
    if (MESSAGE_SETTINGS == 1)
    {
      color_print("Error creating the server","red"); 
    }
    close(SOCKET);
    pointer_reset_all;
    return 0;
  }

  for (;;)
  {
    len = sizeof(cl_addr);
    const int CLIENT_SOCKET = accept(SOCKET, (struct sockaddr *) &cl_addr, (socklen_t*)&len);
    inet_ntop(AF_INET, &(cl_addr.sin_addr), client_address, BUFFER_SIZE);
    if (client_address == NULL)
    {
      if (MESSAGE_SETTINGS == 1)
      {
        color_print("Error accepting connection","red"); 
      }
      continue;
    }
    const size_t CLIENT_ADDRESS_LENGTH = strnlen(client_address,BUFFER_SIZE);
    const size_t BUFFER2_LENGTH = strnlen(buffer2,BUFFER_SIZE);
  
    if (CLIENT_SOCKET == -1)
    {
      if (MESSAGE_SETTINGS == 1)
      {
        memset(string,0,strnlen(string,BUFFER_SIZE));
        memcpy(string,"Error accepting connection from ",32);
        memcpy(string+32,inet_ntoa(cl_addr.sin_addr),CLIENT_ADDRESS_LENGTH);
        memcpy(string+32+CLIENT_ADDRESS_LENGTH," on ",4);
        memcpy(string+36+CLIENT_ADDRESS_LENGTH,buffer2,strnlen(buffer2,BUFFER_SIZE));
        color_print(string,"red"); 
      }
      continue;
    }
    if (MESSAGE_SETTINGS == 1)
    {
      memset(string,0,strnlen(string,BUFFER_SIZE));
      memcpy(string,"Connection accepted from ",25);
      memcpy(string+25,inet_ntoa(cl_addr.sin_addr),CLIENT_ADDRESS_LENGTH);
      memcpy(string+25+CLIENT_ADDRESS_LENGTH," on ",4);
      memcpy(string+29+CLIENT_ADDRESS_LENGTH,buffer2,strnlen(buffer2,BUFFER_SIZE));
      color_print(string,"green"); 
    }

   

    if (fork() == 0)
    { 
       // close the main socket, since the socket is now copied to the forked process
       close(SOCKET); 

       for (;;)
       {         
         // receive the data
         memset(buffer, 0, BUFFER_SIZE); 
         receive_data_result = receive_data(CLIENT_SOCKET,buffer,SOCKET_END_STRING,0,TOTAL_CONNECTION_TIME_SETTINGS);
         if (receive_data_result < 2)
         {
           if (MESSAGE_SETTINGS == 1)
           {
             memset(string,0,strnlen(string,BUFFER_SIZE));
             memcpy(string,"Error receiving data from ",26);
             memcpy(string+26,client_address,CLIENT_ADDRESS_LENGTH);
             memcpy(string+26+CLIENT_ADDRESS_LENGTH," on port ",9);
             memcpy(string+35+CLIENT_ADDRESS_LENGTH,buffer2,BUFFER2_LENGTH);
             if (receive_data_result == 1)
             {
               memcpy(string+35+CLIENT_ADDRESS_LENGTH+BUFFER2_LENGTH,", because of a timeout issue",28);
             }
             else if (receive_data_result == 0)
             {
               memcpy(string+35+CLIENT_ADDRESS_LENGTH+BUFFER2_LENGTH,", because of a potential buffer overflow issue",46);
             }
             color_print(string,"red"); 
           }
           // close the forked process, since the client had an error sending data       
           close(CLIENT_SOCKET);
           pointer_reset_all;
           _exit(0);
         } 



         // check if a certain type of message has been received         
         if (strstr(buffer,"\"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\"") != NULL)
         {
           if (server_received_data_xcash_proof_of_stake_test_data(CLIENT_SOCKET,buffer) == 0)
           {
             // close the forked process, since the client had an error sending data       
             close(CLIENT_SOCKET);
             pointer_reset_all;
             _exit(0);
           }
         }
         else if (strstr(buffer,"\"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\"") != NULL)
         {
           if (server_receive_data_set_xcash_proof_of_stake_settings(CLIENT_SOCKET,buffer) == 0)
           {
             // close the forked process, since the client had an error sending data       
             close(CLIENT_SOCKET);
             pointer_reset_all;
             _exit(0);
           }
         }
         else if (strstr(buffer,"\"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\"") != NULL)
         {
           if (server_receive_data_block_producer_create_block(CLIENT_SOCKET,buffer) == 0)
           {
             // close the forked process, since the client had an error sending data       
             close(CLIENT_SOCKET);
             pointer_reset_all;
             _exit(0);
           }
         }
         else if (strstr(buffer,"\"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\"") != NULL)
         {
           if (server_receive_data_consensus_node_create_block(CLIENT_SOCKET,buffer) == 0)
           {
             // close the forked process, since the client had an error sending data       
             close(CLIENT_SOCKET);
             pointer_reset_all;
             _exit(0);
           }
         }
         else
         {
           printf("Received %s from %s on port %s\r\n",buffer,client_address,buffer2);
           // send the message 
           if (send_data(CLIENT_SOCKET,buffer,1) == 1)
           {
             printf("Sent %s to %s on port %s\r\n",buffer,client_address,buffer2);
           } 
           else
           {
             memset(string,0,strnlen(string,BUFFER_SIZE));
             memcpy(string,"Error sending data to ",22);
             memcpy(string+22,client_address,CLIENT_ADDRESS_LENGTH);
             memcpy(string+22+CLIENT_ADDRESS_LENGTH," on port ",9);
             memcpy(string+31+CLIENT_ADDRESS_LENGTH,buffer2,BUFFER2_LENGTH);
             color_print(string,"red"); 
             continue;
           } 
         }

         
       
       }
     }   
     else
     {
       // if the process did not fork, close the client socket
       close(CLIENT_SOCKET);
     } 
   }
   return 1;
   #undef pointer_reset_all
}

