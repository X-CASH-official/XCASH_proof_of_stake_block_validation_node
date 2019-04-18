#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "network_functions.h"
#include "network_wallet_functions.h"
#include "string_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: get_public_address
Description: Gets the public address of your wallet
Parameters:
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int get_public_address(const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));

  if (data == NULL)
  {
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

  // define macros
  #define GET_PUBLIC_ADDRESS_DATA "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_address\"}"

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,GET_PUBLIC_ADDRESS_DATA,RECEIVE_DATA_TIMEOUT_SETTINGS,"get public address",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset(data);   
    return 0;
  }
  
  if (parse_json_data(data,"address",xcash_wallet_public_address) == 0)
  {
    pointer_reset(data); 
    return 0;
  }
  
  // check if the returned data is valid
  if (strnlen(xcash_wallet_public_address,BUFFER_SIZE) != XCASH_WALLET_LENGTH && strncmp(xcash_wallet_public_address,XCASH_WALLET_PREFIX,3) != 0)
  {
     pointer_reset(data); 
     return 0;
  }
  
  pointer_reset(data); 
  return 1;

  #undef GET_PUBLIC_ADDRESS_DATA
}



/*
-----------------------------------------------------------------------------------------------------------
Name: sign_block_data
Description: Signs the block data, using the wallets address
Parameters:
  DATA - The data to be signed, will hold the result
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int sign_block_data(char* message, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);
  const size_t DATA_LENGTH = strnlen(message,BUFFER_SIZE);

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
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  }

   // define macros
  #define pointer_reset_all \
  free(data); \
  data = NULL; \
  free(data2); \
  data2 = NULL; 

  memcpy(data,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"sign\",\"params\":{\"data\":\"",60);
  memcpy(data+60,message,DATA_LENGTH);
  memcpy(data+60+DATA_LENGTH,"\"}}",3);

  if (send_http_request(data2,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,data,RECEIVE_DATA_TIMEOUT_SETTINGS,"sign data",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset_all;   
    return 0;
  }
  memset(data,0,strnlen(data,BUFFER_SIZE));
  
  if (parse_json_data(data2,"signature",data) == 0)
  {
    pointer_reset_all; 
    return 0;
  }
  
  // check if the returned data is valid
  if (strnlen(data,BUFFER_SIZE) != XCASH_SIGN_DATA_LENGTH && strncmp(data,XCASH_SIGN_DATA_PREFIX,3) != 0)
  {
     pointer_reset_all; 
     return 0;
  }

  memset(message,0,strnlen(message,BUFFER_SIZE));
  memcpy(message,data,strnlen(data,BUFFER_SIZE));
  
  pointer_reset_all; 
  return 1;

  #undef pointer_reset_all
}