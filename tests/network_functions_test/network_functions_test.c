#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "network_wallet_functions.h"
#include "server_functions.h"
#include "string_functions.h"

#include "define_macros_test.h"
#include "variables_test.h"
#include "network_functions_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: network_daemon_test
Description: Test the network_daemon functions
Return: The number of passed network_daemon test
-----------------------------------------------------------------------------------------------------------
*/

void network_daemon_test()
{  
  // Variables
  char* transactions[5];
  size_t count;

  for (count = 0; count < 5; count++)
  {
    transactions[count] = (char*)calloc(BUFFER_SIZE,sizeof(char));
  }

  for (count = 0; count < 5; count++)
  {
    if (transactions[count] == NULL)
    {
      color_print("Could not allocate the memory needed on the heap","red");
      exit(0);
    }
  }

  // reset the variables
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));

  // run the test

  // test the get_block_template function
  if (get_block_template(data_test,"0",0) == 1)
  {   
    color_print("PASSED! Test for getting the block template","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the block template","red");
  }

  // test the get_current_block_height function
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (get_current_block_height(data_test,0) == 1)
  {   
    color_print("PASSED! Test for getting the current block height","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the current block height","red");
  }

  // test the get_previous_block_hash function
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (get_previous_block_hash(data_test,0) == 1)
  {   
    color_print("PASSED! Test for getting the previous block hash","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for getting the previous block hash","red");
  }

  for (count = 0; count < 5; count++)
  {
    pointer_reset(transactions[count]);
  }
}



/*
-----------------------------------------------------------------------------------------------------------
Name: create_server_on_separate_thread
Description: Creates the server on a separate thread
Return: NULL
-----------------------------------------------------------------------------------------------------------
*/

void* create_server_on_separate_thread()
{
  create_server(0);
  pthread_exit((void *)(intptr_t)1);
}



/*
-----------------------------------------------------------------------------------------------------------
Name: general_network_test
Description: Test the network functions
Return: The number of passed general_network test
-----------------------------------------------------------------------------------------------------------
*/

void general_network_test()
{  
  // Variables
  char* message = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));
  int settings = 1;
  pthread_t thread_id;

  // define macros
  #define MESSAGE "{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}"

  #define pointer_reset_all \
  free(message); \
  message = NULL; \
  free(public_address); \
  public_address = NULL; \
  free(string); \
  string = NULL;

  // check if the memory needed was allocated on the heap successfully
  if (message == NULL || public_address == NULL || string == NULL)
  {
    if (message != NULL)
    {
      pointer_reset(message);
    }
    if (public_address != NULL)
    {
      pointer_reset(public_address);
    }
    if (string != NULL)
    {
      pointer_reset(string);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));

  // run the test

  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1); 
  
  // test for creating the server
  if (pthread_create(&thread_id, NULL, &create_server_on_separate_thread,NULL) != 0)
  {
    color_print("FAILED! Test for creating the server","red");
    color_print("FAILED! Test for sending and receving data using sockets","red");
    settings = 0;
  }
  if (settings == 1)
  {
    if (pthread_detach(thread_id) != 0)
    {      
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }  
  }
  sleep(1);



  // test for sending and receiving data using sockets
  // create the message
  memset(message,0,strnlen(message,BUFFER_SIZE));
  append_string(message,MESSAGE);

  // sign_data
  if (settings == 1)
  {
    if (sign_data(message,0) == 0)
    { 
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
    }
  }
 
  if (settings == 1)
  {
    if (send_and_receive_data_socket(string,"127.0.0.1",SEND_DATA_PORT,message,TOTAL_CONNECTION_TIME_SETTINGS,"XCASH_PROOF_OF_STAKE_TEST_DATA",0) <= 0)
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));

  // verify the message
  if (settings == 1)
  {
    if (verify_data(string,0,1,1) == 0)
    {   
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }

  // parse the data
  if (settings == 1)
  {
    if (parse_json_data(string,"message_settings",data_test) == 0)
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }
  
  // check if the received data is correct
  if (settings == 1)
  {
    if (strncmp(data_test,"XCASH_PROOF_OF_STAKE_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for creating the server","green");
      color_print("PASSED! Test for sending and receving data using sockets","green");
      count_test += 2;
    }
    else
    {
      color_print("FAILED! Test for creating the server","red");
      color_print("FAILED! Test for sending and receving data using sockets","red");
      settings = 0;
    }
  }

  pointer_reset_all;

  #undef MESSAGE
  #undef pointer_reset_all
}



/*
-----------------------------------------------------------------------------------------------------------
Name: network_security_test
Description: Test the network_security functions
Return: The number of passed network_security test
-----------------------------------------------------------------------------------------------------------
*/

void network_security_test()
{  
  // define macros
  #define MESSAGE "{\r\n \"message_settings\": \"XCASH_PROOF_OF_STAKE_TEST_DATA\",\r\n}"
  
  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));

  // set the current_round_part and current_round_part_backup_node
  memset(current_round_part,0,strnlen(current_round_part,BUFFER_SIZE));
  memset(current_round_part_backup_node,0,strnlen(current_round_part_backup_node,BUFFER_SIZE));
  memcpy(current_round_part,"1",1);
  memcpy(current_round_part_backup_node,"0",1);
  
  // create the message
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  append_string(result_test,MESSAGE);

  // test the sign_data functions
  if (sign_data(result_test,0) == 1)
  {   
    color_print("PASSED! Test for sign data to send data securely","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for sign data to send data securely","red");
  }
  
  // test the verify_data functions
  if (verify_data(result_test,0,1,1) == 1)
  {   
    color_print("PASSED! Test for verify data to receive data securely","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for verify data to receive data securely","red");
  }
  #undef MESSAGE
}



/*
-----------------------------------------------------------------------------------------------------------
Name: network_wallet_test
Description: Test the network_wallet functions
Return: The number of passed network_wallet test
-----------------------------------------------------------------------------------------------------------
*/

void network_wallet_test()
{ 
  // test the get_public_address function
  memset(xcash_wallet_public_address,0,strnlen(xcash_wallet_public_address,BUFFER_SIZE));
  if (get_public_address(0) == 1)
  {   
    color_print("PASSED! Test for sending an HTTP request and getting the public address of the opened X-CASH wallet","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for sending an HTTP request and getting the public address of the opened X-CASH wallet","red");
  }

  // test the sign_block_data function
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(data_test,"XCASH_PROOF_OF_STAKE_TEST_DATA",30);
  if (sign_block_data(data_test,0) == 1 && memcmp(data_test,"SigV1",5) == 0 && strlen(data_test) == XCASH_SIGN_DATA_LENGTH)
  {   
    color_print("PASSED! Test for sign block data","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for sign block data","red");
  }
}



/*
-----------------------------------------------------------------------------------------------------------
Name: network_test
Description: Runs all of the network test
Return: The number of passed network test
-----------------------------------------------------------------------------------------------------------
*/

int network_functions_test()
{
  // define macros
  #define NETWORK_TOTAL_TEST 9

  // reset the varaibles
  count_test = 0;

  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mnetwork test - Total test: %d\033[0m\n",NETWORK_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");

  // run the test
  network_daemon_test();
  general_network_test();
  network_security_test();
  network_wallet_test();

  // write the end test message
  if (count_test == NETWORK_TOTAL_TEST)
  {
    printf("\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mnetwork test - Passed test: %d, Failed test: 0\033[0m\n",NETWORK_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mnetwork test - Passed test: %d, Failed test: %d\033[0m\n",count_test,NETWORK_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  }
  return count_test;

  #undef NETWORK_TOTAL_TEST
}
