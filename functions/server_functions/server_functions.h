#ifndef SERVER_FUNCTIONS_H_   /* Include guard */
#define SERVER_FUNCTIONS_H_

/*
-----------------------------------------------------------------------------------------------------------
Function prototypes
-----------------------------------------------------------------------------------------------------------
*/

int get_current_consensus_nodes_IP_address();
int server_received_data_xcash_proof_of_stake_test_data(const int CLIENT_SOCKET, char* message);
int server_receive_data_set_xcash_proof_of_stake_settings(const int CLIENT_SOCKET, char* MESSAGE);
int server_receive_data_block_producer_create_block(const int CLIENT_SOCKET, char* MESSAGE);
int server_receive_data_consensus_node_create_block(const int CLIENT_SOCKET, char* MESSAGE);
int create_server(const int MESSAGE_SETTINGS);
#endif