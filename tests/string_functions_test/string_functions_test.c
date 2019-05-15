#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "define_macro_functions.h"
#include "define_macros.h"
#include "structures.h"

#include "string_functions.h"

#include "define_macros_test.h"
#include "variables_test.h"
#include "string_functions_test.h"

/*
-----------------------------------------------------------------------------------------------------------
Functions
-----------------------------------------------------------------------------------------------------------
*/

/*
-----------------------------------------------------------------------------------------------------------
Name: string_functions_test
Description: Test the string functions
Return: The number of passed string_functions test
-----------------------------------------------------------------------------------------------------------
*/

int string_functions_test()
{  
  // Variables
  int settings = 1;

  // define macros
  #define STRING_FUNCTIONS_TOTAL_TEST 12
 
  #define SIGN_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"xcash_proof_of_stake_signature\": \"SIGN_RPC_CALL_TEST_DATA\"\r\n  }\r\n}"
  #define VERIFY_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"good\": VERIFY_RPC_CALL_TEST_DATA\r\n  }\r\n}"
  #define GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA "{\r\n  \"id\": \"0\",\r\n  \"jsonrpc\": \"2.0\",\r\n  \"result\": {\r\n    \"blockhashing_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"blocktemplate_blob\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"difficulty\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"expected_reward\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"height\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"prev_hash\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"reserved_offset\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,\r\n    \"status\": \"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\",\r\n    \"untrusted\": GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA\r\n  }\r\n}"
 
/*
  This message is sent from the Consensus node in the xcash_proof_of_stake function and received by the consensus node private key in the receive_xcash_proof_of_stake_settings function.
 
  The purpose of this message is for the consensus node to get the xcash_proof_of_stake_settings
 
  message_settings - The type of the message
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"data\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"


/*
  This message is sent from the Consensus node private key in the receive_xcash_proof_of_stake_settings function and received by the consensus node in the xcash_proof_of_stake function.
 
  The purpose of this message is for the consensus node private key to return the receive_xcash_proof_of_stake_settings to the consensus node.
 
  message_settings - The type of the message
  xcash_proof_of_stake_settings - The xcash_proof_of_stake_settings (0 or 1)
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS "{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"public_address\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"previous_block_hash\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"current_round_part_backup_node\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"data\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n \"xcash_proof_of_stake_signature\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS\",\r\n}"

/*
  This message is sent from the consensus node in the consensus_node_create_new_block function and received by the block validation node in the consensus_node_create_new_block function.
 
  The purpose of this message is for the consensus node to create a block without the delegates
 
  message_settings - The type of the message
  block_blob - The block blob
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"

  /*
  This message is sent from the block validation node in the consensus_node_create_new_block function and received by the consensus node in the consensus_node_create_new_block function.
 
  The purpose of this message is for the block validation node to sign the block_blob that the consensus node created so the block will be valid and can be added to the network to create a block without the delegates
 
  message_settings - The type of the message
  block_blob_signature - The block blob signature
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob_signature\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"

  /*
  This message is sent from the consensus node in the create_new_block function and received by the block validators in the create_new_block function.
 
  The purpose of this message is for the consensus node to submit the block to the network that the block producer has created.
 
  message_settings - The type of the message  
  block_blob - The block blob
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK\",\r\n}"

  /*
  This message is sent from the consensus node private key in the create_new_block function and received by the consensus node in the create_new_block function.
 
  The purpose of this message is for the block validator to sign the block_blob so the block will be valid and can be added to the network
 
  message_settings - The type of the message
  block_blob_signature - The block blob signature
  public_address - The public address of the node that is sending the data.
  previous_block_hash - The previous block hash.
  current_round_part - The current round part (1-4).
  current_round_part_backup_node - The current main node in the current round part (0-5)
  data - A random 100 character string. This is the data that the xcash_proof_of_stake_signature is used for. The random data  will create a different xcash_proof_of_stake_signature for every message, even if the message data is the same.
  xcash_proof_of_stake_signature - The xcash_proof_of_stake_signature of the data, used for verifying that the sender of the message is the sender.
  */
  #define BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK "{\r\n \"message_settings\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"block_blob_signature\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"public_address\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"previous_block_hash\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"current_round_part_backup_node\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"data\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n \"xcash_proof_of_stake_signature\": \"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CREATE_NEW_BLOCK\",\r\n}"

  // reset the variables
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  count_test = 0;
 
  // write the start test message
  color_print(TEST_OUTLINE,"blue");
  printf("\033[1;34mstring functions test - Total test: %d\033[0m\n",STRING_FUNCTIONS_TOTAL_TEST);
  color_print(TEST_OUTLINE,"blue");
  printf("\n");
 
  // run the test
 
  // test parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field
  memcpy(result_test,SIGN_RPC_CALL_TEST_DATA,strnlen(SIGN_RPC_CALL_TEST_DATA,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"SIGN_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the sign RPC call for the xcash_proof_of_stake_signature field","red");
  }
 
  // test parsing the return data for the verify RPC call for the good field
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,VERIFY_RPC_CALL_TEST_DATA,strnlen(VERIFY_RPC_CALL_TEST_DATA,BUFFER_SIZE));
  if (parse_json_data(result_test,"good",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"VERIFY_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the verify RPC call for the good field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the verify RPC call for the good field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the verify RPC call for the good field","red");
  }
 
  // test parsing the return data for the get_block_template RPC call for the blocktemplate_blob field
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,strnlen(GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA,BUFFER_SIZE));
  if (parse_json_data(result_test,"blocktemplate_blob",data_test) != 0)
  {
    // check if the data is correct
    if (strncmp(data_test,"GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA",BUFFER_SIZE) == 0)
    {
      color_print("PASSED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","green");
      count_test++;
    }
    else
    {
      color_print("FAILED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","red");
    }
  }
  else
  {
    color_print("FAILED! Test for parsing the return data for the get_block_template RPC call for the blocktemplate_blob field","red");
  }



  // test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS,strnlen(CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  else
  {
    color_print("PASSED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS","green");
    count_test++;
  }
  settings = 1;



  // test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS,strnlen(BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_settings",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","red");
  }
  else
  {
    color_print("PASSED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS","green");
    count_test++;
  }
  settings = 1;



  // test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,strnlen(CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"block_blob",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  else
  {
    color_print("PASSED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
    count_test++;
  }
  settings = 1;



  // test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,strnlen(BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"block_blob_signature",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  else
  {
    color_print("PASSED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
    count_test++;
  }
  settings = 1;



  // test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK,strnlen(CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"block_blob",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK","red");
  }
  else
  {
    color_print("PASSED! Test for parsing CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK","green");
    count_test++;
  }
  settings = 1;



  // test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  memcpy(result_test,BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,strnlen(BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK,BUFFER_SIZE));
  if (parse_json_data(result_test,"message_settings",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"block_blob_signature",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"public_address",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"previous_block_hash",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"current_round_part_backup_node",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"data",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (parse_json_data(result_test,"xcash_proof_of_stake_signature",data_test) == 0 || strncmp(data_test,"BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK",BUFFER_SIZE) != 0)
  {
    settings = 0;
  }
  memset(data_test,0,strnlen(data_test,BUFFER_SIZE));
  if (settings == 0)
  {
    color_print("FAILED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","red");
  }
  else
  {
    color_print("PASSED! Test for parsing BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK","green");
    count_test++;
  }
  settings = 1;

  // test for creating a random string
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  if (random_string(result_test,RANDOM_STRING_LENGTH) == 1)
  {   
    color_print("PASSED! Test for creating a random string","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for creating a random string","red");
  }

  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  memcpy(result_test,TEST_OUTLINE,strnlen(TEST_OUTLINE,BUFFER_SIZE));

  // test for counting occurences of a substring in a string
  if (string_count(result_test,"-") == strnlen(TEST_OUTLINE,BUFFER_SIZE) && string_count(result_test,"--") == strnlen(TEST_OUTLINE,BUFFER_SIZE)/2)  
  {
    color_print("PASSED! Test for counting occurences of a substring in a string","green");
    count_test++;
  }
  else
  {
    color_print("FAILED! Test for counting occurences of a substring in a string","red");
  }

  // test for string replace
  memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
  append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
  if (string_replace(result_test,"string_replace_test","string_replace") == 1 && strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
  {
    memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
    append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
     if (string_replace(result_test,"\"","\\\"") == 1 && strncmp(result_test,"{\r\n \\\"message_settings\\\": \\\"string_replace_test\\\",\r\n}",BUFFER_SIZE) == 0)
     {
       memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
       append_string(result_test,"{\r\n \"message_settings\": \"string_replace_test\",\r\n}");
       if (string_replace(result_test,"_test","") == 1 && strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
       {
         memset(result_test,0,strnlen(result_test,BUFFER_SIZE));
         append_string(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}");
         if (string_replace(result_test,"string_replace_test","") == 0 && strncmp(result_test,"{\r\n \"message_settings\": \"string_replace\",\r\n}",BUFFER_SIZE) == 0)
         {    
           color_print("PASSED! Test for string replace","green");
           count_test++;
         }
         else
         {
           color_print("FAILED! Test for string replace","red");
         }
       }
       else
       {
         color_print("FAILED! Test for string replace","red");
       }
     }
     else
     {
       color_print("FAILED! Test for string replace","red");
     }
  }
  else
  {
    color_print("FAILED! Test for string replace","red");
  }
 
  // write the end test message
  if (count_test == STRING_FUNCTIONS_TOTAL_TEST)
  {
    printf("\n\n");
    color_print(TEST_OUTLINE,"green");
    printf("\033[1;32mstring functions test - Passed test: %d, Failed test: 0\033[0m\n",STRING_FUNCTIONS_TOTAL_TEST);
    color_print(TEST_OUTLINE,"green");
    printf("\n\n");
  }
  else
  {
    printf("\n\n");
    color_print(TEST_OUTLINE,"red");
    printf("\033[1;31mstring functions test - Passed test: %d, Failed test: %d\033[0m\n",count_test,STRING_FUNCTIONS_TOTAL_TEST-count_test);
    color_print(TEST_OUTLINE,"red");
    printf("\n\n");
  }
  return count_test;

  #undef STRING_COUNT_TOTAL_TEST
  #undef SIGN_RPC_CALL_TEST_DATA
  #undef VERIFY_RPC_CALL_TEST_DATA
  #undef GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA
  #undef CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_RECEIVE_XCASH_PROOF_OF_STAKE_SETTINGS
  #undef GET_BLOCK_TEMPLATE_RPC_CALL_TEST_DATA
  #undef BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_SEND_XCASH_PROOF_OF_STAKE_SETTINGS
  #undef BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK
  #undef CONSENSUS_NODE_TO_BLOCK_VALIDATION_NODE_CREATE_NEW_BLOCK
  #undef BLOCK_VALIDATION_NODE_TO_CONSENSUS_NODE_CONSENSUS_NODE_CREATE_NEW_BLOCK  
}