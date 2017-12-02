#define WIN32_LEAN_AND_MEAN
#include "stdafx.h"
#include <winsock2.h>
#include <process.h>
#include <iostream>
//#include "PasswdGen.h"
#include "..\Include\PasswdGen.h"


using namespace std;
#pragma comment(lib,"ws2_32.lib" )
#define MAX_THREADS 100

struct SockAccept
{
	SOCKET client;
	string pwd;
};

class Ssocket
{
private:
	WSADATA wsaData;
	//int iResult;
	sockaddr_in addr;
	SOCKET sock, client;
	SockAccept client2;
	HANDLE handle[MAX_THREADS];
	PasswdGen pg;


	int setServerIPstr(string serverIP);
	int setServerPORTstr(int serverPORT);
	int setWSA();
	int createSock();
	int bindServer();
	int listServer();
	int connectToServer();

public:
	Ssocket();
	~Ssocket();
	int runServer(string serverIP, int serverPORT);
	int connectClient(string serverIP, int serverPORT);
	string getServerIPstr();
	string getServerPORTstr();
	SOCKET * getSock();
	static unsigned int __stdcall ServClient(void *data);
};