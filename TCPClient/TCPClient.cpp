// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\TCPServer\socket.h"



int main()
{
	Ssocket Sclient;
	Sclient.connectClient("127.0.0.1", 2222);

	SOCKET * sPTR = Sclient.getSock();
	SOCKET sock = *sPTR;

	char ptr[100];
	for (int i = 0; i<100; i++)
	{
		Sleep(300);
		sprintf(ptr, "Heartbeat %d", i);
		send(sock, ptr, sizeof(ptr), 0); // nuzhna proverka

	}
	shutdown(sock, SD_BOTH);
	closesocket(sock);

	return 0;

}

