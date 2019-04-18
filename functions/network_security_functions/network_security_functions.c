#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "variables.h"

#include "define_macros_functions.h"
#include "network_daemon_functions.h"
#include "network_functions.h"
#include "network_security_functions.h"
#include "string_functions.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: sign_data
Description: Signs data with your XCA address, for sending data securely
Parameters:
  message - The sign_data
  MESSAGE_SETTINGS - 1 to print the messages, otherwise 0. This is used for the testing flag to not print any success or error messages
Return: 0 if an error has occured, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int sign_data(char *message, const int HTTP_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);

  // Variables
  char* previous_block_hash = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* random_data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* result = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));

  // define macros
  #define pointer_reset_all \
  free(previous_block_hash); \
  previous_block_hash = NULL; \
  free(random_data); \
  random_data = NULL; \
  free(result); \
  result = NULL; \
  free(data); \
  data = NULL; \
  free(string); \
  string = NULL;

  // check if the memory needed was allocated on the heap successfully
  if (previous_block_hash == NULL || random_data == NULL || result == NULL || data == NULL || string == NULL)
  {
    if (previous_block_hash != NULL)
    {
      pointer_reset(previous_block_hash);
    }
    if (random_data != NULL)
    {
      pointer_reset(random_data);
    }
    if (result != NULL)
    {
      pointer_reset(result);
    }
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (string != NULL)
    {
      pointer_reset(string);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  } 

  // create the random data
  if (random_string(random_data,RANDOM_STRING_LENGTH) == 0)
  {
    pointer_reset_all; 
    return 0;
  }

  // get the previous block hash
  if (get_previous_block_hash(previous_block_hash,0) == 0)
  {  
    pointer_reset_all;
    return 0;
  }

  // create the message
  size_t message_length = strnlen(message,BUFFER_SIZE)-1;
  const size_t previous_block_hash_LENGTH = strnlen(previous_block_hash,BUFFER_SIZE);
  memcpy(result,message,message_length);
  memcpy(result+message_length," \"public_address\": \"",20);
  memcpy(result+message_length+20,xcash_wallet_public_address,XCASH_WALLET_LENGTH);
  memcpy(result+message_length+20+XCASH_WALLET_LENGTH,"\",\r\n \"previous_block_hash\": \"",29);
  memcpy(result+message_length+49+XCASH_WALLET_LENGTH,previous_block_hash,previous_block_hash_LENGTH);  
  memcpy(result+message_length+49+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"current_round_part\": \"",28);
  memcpy(result+message_length+77+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,current_round_part,1);
  memcpy(result+message_length+78+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"current_round_part_backup_node\": \"",40);
  memcpy(result+message_length+118+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,current_round_part_backup_node,1);
  memcpy(result+message_length+119+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"data\": \"",14);
  memcpy(result+message_length+133+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,random_data,RANDOM_STRING_LENGTH);
  memcpy(result+message_length+133+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH+RANDOM_STRING_LENGTH,"\",\r\n}",5);

  // format the message
  if (string_replace(result,"\"","\\\"") == 0)
  {
    pointer_reset_all; 
    return 0;
  }

  // sign_data
  const size_t RESULT_LENGTH = strnlen(result,BUFFER_SIZE);
  memcpy(string,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"sign\",\"params\":{\"data\":\"",60);
  memcpy(string+60,result,RESULT_LENGTH);
  memcpy(string+60+RESULT_LENGTH,"\"}}",3);
  memset(result,0,RESULT_LENGTH);

  if (send_http_request(data,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,string,RECEIVE_DATA_TIMEOUT_SETTINGS,"sign data",HTTP_SETTINGS) <= 0)
  {  
    pointer_reset_all;
    return 0;
  } 

  if (parse_json_data(data,"signature",result) == 0)
  {
    pointer_reset_all;
    return 0;
  }

  // check if the returned data is valid
  if (strnlen(result,BUFFER_SIZE) != XCASH_SIGN_DATA_LENGTH && strncmp(result,XCASH_SIGN_DATA_PREFIX,5) != 0)
  {
    pointer_reset_all;
    return 0;
  }
  
  // create the message
  message_length = strnlen(message,BUFFER_SIZE) - 1;
  const size_t XCASH_PROOF_OF_STAKE_SIGNATURE_LENGTH = strnlen(result,BUFFER_SIZE);
  
  memcpy(message+message_length," \"public_address\": \"",20);
  memcpy(message+message_length+20,xcash_wallet_public_address,XCASH_WALLET_LENGTH);
  memcpy(message+message_length+20+XCASH_WALLET_LENGTH,"\",\r\n \"previous_block_hash\": \"",29);
  memcpy(message+message_length+49+XCASH_WALLET_LENGTH,previous_block_hash,previous_block_hash_LENGTH);  
  memcpy(message+message_length+49+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"current_round_part\": \"",28);
  memcpy(message+message_length+77+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,current_round_part,1);
  memcpy(message+message_length+78+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"current_round_part_backup_node\": \"",40);
  memcpy(message+message_length+118+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,current_round_part_backup_node,1);
  memcpy(message+message_length+119+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,"\",\r\n \"data\": \"",14);
  memcpy(message+message_length+133+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH,random_data,RANDOM_STRING_LENGTH);
  memcpy(message+message_length+133+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH+RANDOM_STRING_LENGTH,"\",\r\n \"xcash_proof_of_stake_signature\": \"",40);
  memcpy(message+message_length+173+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH+RANDOM_STRING_LENGTH,result,XCASH_PROOF_OF_STAKE_SIGNATURE_LENGTH);
  memcpy(message+message_length+173+XCASH_WALLET_LENGTH+previous_block_hash_LENGTH+RANDOM_STRING_LENGTH+XCASH_PROOF_OF_STAKE_SIGNATURE_LENGTH,"\",\r\n}",5);

  pointer_reset_all;
  return 1;
  
  #undef pointer_reset_all
}


/*
-----------------------------------------------------------------------------------------------------------
Name: verify_data
Description: Verifies signed data, for receiving data securely
Parameters:
  message - The signed data
  HTTP_SETTINGS - The http settings
  VERIFY_CURRENT_ROUND_PART_SETTINGS - 1 to verify the current_round_part, otherwise 0
  VERIFY_CURRENT_ROUND_PART_BACKUP_NODE_SETTINGS - 1 to verify the current_round_part_backup_node, otherwise 0
Return: 0 if the signed data is not verified, 1 if successfull
-----------------------------------------------------------------------------------------------------------
*/

int verify_data(const char* MESSAGE, const int HTTP_SETTINGS, const int VERIFY_CURRENT_ROUND_PART_SETTINGS, const int VERIFY_CURRENT_ROUND_PART_BACKUP_NODE_SETTINGS)
{
  // Constants
  const char* HTTP_HEADERS[] = {"Content-Type: application/json","Accept: application/json"}; 
  const size_t HTTP_HEADERS_LENGTH = sizeof(HTTP_HEADERS)/sizeof(HTTP_HEADERS[0]);
  
  // Variables
  char* message_settings = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* public_address = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* previous_block_hash = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message_previous_block_hash = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message_current_round_part = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* message_current_round_part_backup_node = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* xcash_proof_of_stake_signature = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* result = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* data = (char*)calloc(BUFFER_SIZE,sizeof(char));
  char* string = (char*)calloc(BUFFER_SIZE,sizeof(char));
  size_t message_length = strnlen(MESSAGE,BUFFER_SIZE) - 134;

  // define macros
  #define pointer_reset_all \
  free(message_settings); \
  message_settings = NULL; \
  free(public_address); \
  public_address = NULL; \
  free(previous_block_hash); \
  previous_block_hash = NULL; \
  free(message_previous_block_hash); \
  message_previous_block_hash = NULL; \
  free(message_current_round_part); \
  message_current_round_part = NULL; \
  free(message_current_round_part_backup_node); \
  message_current_round_part_backup_node = NULL; \
  free(xcash_proof_of_stake_signature); \
  xcash_proof_of_stake_signature = NULL; \
  free(result); \
  result = NULL; \
  free(data); \
  data = NULL; \
  free(string); \
  string = NULL;

  // check if the memory needed was allocated on the heap successfully
  if (message_settings == NULL || public_address == NULL || previous_block_hash == NULL || message_previous_block_hash == NULL || message_current_round_part == NULL || message_current_round_part_backup_node == NULL || xcash_proof_of_stake_signature == NULL || result == NULL || data == NULL || string == NULL)
  {
    if (message_settings != NULL)
    {
      pointer_reset(message_settings);
    }
    if (public_address != NULL)
    {
      pointer_reset(public_address);
    }
    if (previous_block_hash != NULL)
    {
      pointer_reset(previous_block_hash);
    }
    if (message_previous_block_hash != NULL)
    {
      pointer_reset(message_previous_block_hash);
    }
    if (message_current_round_part != NULL)
    {
      pointer_reset(message_current_round_part);
    }
    if (message_current_round_part_backup_node != NULL)
    {
      pointer_reset(message_current_round_part_backup_node);
    }
    if (xcash_proof_of_stake_signature != NULL)
    {
      pointer_reset(xcash_proof_of_stake_signature);
    }
    if (result != NULL)
    {
      pointer_reset(result);
    }
    if (data != NULL)
    {
      pointer_reset(data);
    }
    if (string != NULL)
    {
      pointer_reset(string);
    }
    color_print("Could not allocate the memory needed on the heap","red");
    exit(0);
  } 

  // parse the message
  if (parse_json_data(MESSAGE,"message_settings",message_settings) == 0 || parse_json_data(MESSAGE,"public_address",public_address) == 0 || parse_json_data(MESSAGE,"previous_block_hash",message_previous_block_hash) == 0 || parse_json_data(MESSAGE,"current_round_part",message_current_round_part) == 0 || parse_json_data(MESSAGE,"current_round_part_backup_node",message_current_round_part_backup_node) == 0 || parse_json_data(MESSAGE,"xcash_proof_of_stake_signature",xcash_proof_of_stake_signature) == 0)
  {
    pointer_reset_all;
    return 0;
  }

  // verify if the message came from the correct node
  if (strncmp(message_settings,"CONSENSUS_NODE_TO_NODE_RECEIVE_CURRENT_CONSENSUS_NODE_IP_ADDRESS",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODE_RECEIVE_UPDATED_NODE_LIST",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_MAIN_NODE_PUBLIC_ADDRESS",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_MAIN_NODE_START_PART_OF_ROUND",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_LIST_OF_ENABLED_NODES",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_ROUND_CHANGE",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_CONSENSUS_NODE_CHANGE",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_XCASH_PROOF_OF_STAKE_MESSAGE",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEW_PART_OF_ROUND",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_NEXT_ROUND",BUFFER_SIZE) == 0 || strncmp(message_settings,"CONSENSUS_NODE_TO_NODES_AND_MAIN_NODES_RECALCULATING_VOTES",BUFFER_SIZE) == 0)
  {
    if (strncmp(public_address,CONSENSUS_NODE_PUBLIC_ADDRESS,BUFFER_SIZE) != 0)
    {
      pointer_reset_all;
      return 0;
    }
  }



  // verify if the previous block hash is correct
  if (get_previous_block_hash(previous_block_hash,0) == 0)
  {  
    pointer_reset_all;
    return 0;
  }
  if (strncmp(previous_block_hash,message_previous_block_hash,BUFFER_SIZE) != 0)
  {
    pointer_reset_all;
    return 0;
  }

  // verify if the current_round_part is correct
  if (VERIFY_CURRENT_ROUND_PART_SETTINGS == 1)
  {
    if (strncmp(current_round_part,message_current_round_part,BUFFER_SIZE) != 0)
    {
      pointer_reset_all;
      return 0;
    }
  }

  // verify if the current_round_part_backup_node
  if (VERIFY_CURRENT_ROUND_PART_BACKUP_NODE_SETTINGS == 1)
  {
    if (strncmp(current_round_part_backup_node,message_current_round_part_backup_node,BUFFER_SIZE) != 0)
    {
      pointer_reset_all;
      return 0;
    }
  }
  
  // create the message
  memcpy(result,MESSAGE,message_length);
  memcpy(result+message_length,"}",1);
  if (string_replace(result,"\"","\\\"") == 0)
  {
    pointer_reset_all;
    return 0;
  } 
    
  // create the message
  message_length = strnlen(result,BUFFER_SIZE);
  memcpy(string,"{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"verify\",\"params\":{\"data\":\"",62);
  memcpy(string+62,result,message_length);
  memcpy(string+62+message_length,"\",\"address\":\"",13);
  memcpy(string+75+message_length,public_address,XCASH_WALLET_LENGTH);
  memcpy(string+75+message_length+XCASH_WALLET_LENGTH,"\",\"signature\":\"",15);
  memcpy(string+90+message_length+XCASH_WALLET_LENGTH,xcash_proof_of_stake_signature,XCASH_SIGN_DATA_LENGTH);
  memcpy(string+90+message_length+XCASH_WALLET_LENGTH+XCASH_SIGN_DATA_LENGTH,"\"}}",3);
  memset(result,0,strnlen(result,BUFFER_SIZE));

  if (send_http_request(result,"127.0.0.1","/json_rpc",XCASH_WALLET_PORT,"POST", HTTP_HEADERS, HTTP_HEADERS_LENGTH,string,RECEIVE_DATA_TIMEOUT_SETTINGS,"verify data",HTTP_SETTINGS) <= 0)
  { 
    pointer_reset_all; 
    return 0;
  } 
    
  if (parse_json_data(result,"good",data) == 0)
  {
    pointer_reset_all;
    return 0;
  }

  // check if the returned data is valid
  if (strncmp(data,"true",BUFFER_SIZE) != 0)
  {
     pointer_reset_all; 
     return 0;
  }
 
  pointer_reset_all;
  return 1;
  
  #undef pointer_reset_all
}