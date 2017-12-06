// TCPClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\Include\socket.h"

using namespace std;
int main()
{
	Ssocket Sclient;
	

	
	for (int i = 0; i<100; i++)
	{
		//Sclient.sendData("test1" + std::to_string(i));
		Sclient.connectClient("127.0.0.1", 2222);
		Sclient.receiveData(200);
		Sleep(100);
		Sclient.sendData("Test - "+to_string(i));
		Sclient.closeSocket();
	}
	
	

	return 0;

}

