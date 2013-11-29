#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#pragma comment (lib, "ws2_32.lib")

void timer (int sec);
int main (int argc, char *argv [])
{
	WSADATA wsa;
	SOCKET sck,retSocket;
	int cnt,c;
	struct sockaddr_in ip_info,server;
	char server_reply[2000];
	int recv_size;
	char msg [100];



	if (WSAStartup (MAKEWORD (2,2), &wsa) == INVALID_SOCKET)
		printf ("WSA error\n");
	else if ((sck = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		printf ("Socket error\n");
	else{
		ip_info.sin_addr.s_addr = inet_addr("127.0.0.1");
		ip_info.sin_family = AF_INET;
		ip_info.sin_port = htons (8888);
	}

	if (connect (sck, (struct sockaddr *)&ip_info, sizeof (ip_info)) < 0)
		printf ("\nNot connected\n");
	else
		printf ("\nSession is up\n");

	//retSocket = accept(sck , (struct sockaddr *)&server, &c);
	while(1){
		printf("\n");
		printf ("Send: ");
		gets(msg);

		if(send(sck , msg , strlen(msg) , 0) == SOCKET_ERROR)
			puts("fail");
		else
			printf("Message Successfully sent to Server\n");
		
		recv_size = recv(sck, server_reply, 2000, 0);
		server_reply[recv_size] = '\0';
		if ( recv_size== SOCKET_ERROR) {
			puts("recv failed");
		} else { 
			
			printf("Received from server: ");
			puts(server_reply);
		}
	}
	/*while (recv_size = recv(sck, server_reply, 2000, 0)) {
		if (recv_size == SOCKET_ERROR) {
			puts("recv failed");
		} else { 
			server_reply[recv_size] = '\0';
			puts(server_reply);
		}
	}*/




	getch ();
	closesocket(sck);
    return 0;
}


// Timer fucntioN: 
void timer (int sec)
{
	clock_t end;

	end = clock () + sec * CLOCKS_PER_SEC;
	while (clock () <= end);
}