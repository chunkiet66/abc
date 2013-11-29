#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
int main(int argc , char *argv[])
{
	//declare all variables
	WSADATA wsa ;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	char msg [100];
	int recv_size;
	char client_reply[2000];

	//initialising Winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//create socket
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");
	//set socket's information
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr ("127.0.0.1");
	server.sin_port = htons( 8888 );


	//bind socket
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
	}
	printf("Bind done...");
	listen(s , 3);

	//connect to client
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

	puts("Connection accepted");

	//loop forever
	while (1) {
		printf("\n");
		//get the size of received message
		recv_size = recv(new_socket, client_reply, 2000, 0);
		if (recv_size == SOCKET_ERROR) {
			puts("recv failed");
		} else { 
			client_reply[recv_size] = '\0';
			printf("Receive: ");
			puts(client_reply);//print out the message from client
		}
		printf("Successfully received message\n");
		//send the message back to client
		if(send(new_socket , client_reply , strlen(client_reply) , 0) == SOCKET_ERROR)
			puts("fail to reply the client.\n");
		else
			printf("Message Successfully sent back to Client\n");


	}
	//close socket
	closesocket(s);
	closesocket(new_socket);
	return 0;
}

