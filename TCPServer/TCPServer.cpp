// TCPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\Include\socket.h"
#include "..\Include\PasswdGen.h"


void showpwd();

int main()
{
	showpwd();
	PasswdGen pg("01");
//	PasswdGen pg;
	Ssocket ServerSocket;
	ServerSocket.runServer("0.0.0.0", 2222);
	return 0;
}

void showpwd()
{

	PasswdGen pg("01");
	for (int i = 0; i < 10000; i++)
	{
		string s = pg.getNextPWD();
		if (pg.genStop == 0)
			cout << s << endl;
		else
			break;
	}
}

