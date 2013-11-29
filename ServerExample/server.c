#include<io.h>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
int main(int argc , char *argv[])
{

	WSADATA wsa ;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c;
	char msg [100];
	int recv_size;
	char client_reply[2000];

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");


	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr ("127.0.0.1");
	server.sin_port = htons( 8888 );



	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
	}
	printf("Bind done...");
	listen(s , 3);

	
	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

	puts("Connection accepted");
	/*while(1){
		printf ("Send: ");
		gets(msg);

		send(s , msg , strlen(msg) , 0);
	}*/

	while (1) {
		printf("\n");
		recv_size = recv(new_socket, client_reply, 2000, 0);
		if (recv_size == SOCKET_ERROR) {
			puts("recv failed");
		} else { 
			client_reply[recv_size] = '\0';
			printf("Receive: ");
			puts(client_reply);
		}
		printf("Successfully received message\n");

		if(send(new_socket , client_reply , strlen(client_reply) , 0) == SOCKET_ERROR)
			puts("fail to reply the client.\n");
		else
			printf("Message Successfully sent back to Client\n");


	}
	closesocket(s);
	closesocket(new_socket);
	return 0;
}

