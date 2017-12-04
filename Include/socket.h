#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <process.h>
#include <iostream>
#include "PasswdGen.h"
#include <string>



#pragma comment(lib,"ws2_32.lib" )
#define MAX_THREADS 100
#define SendDataLenght 100
#define SendDataTimeout 200

struct SockAccept
{
	SOCKET client;
	std::string pwd;
};

using namespace std;

static class Ssocket
{
private:
	WSADATA wsaData;
	//int iResult;
	sockaddr_in addr;
	static SOCKET sock, client;
	SockAccept client2;
	HANDLE handle[MAX_THREADS];
	PasswdGen pg;


	int setServerIPstr(std::string serverIP);
	int setServerPORTstr(int serverPORT);
	int setWSA();
	int createSock();
	int bindServer();
	int listServer();
	int connectToServer();

public:
	Ssocket();
	~Ssocket();
	int runServer(std::string serverIP, int serverPORT);
	int connectClient(std::string serverIP, int serverPORT);
	std::string getServerIPstr();
	std::string getServerPORTstr();
	SOCKET * getSock();
	int dl = SendDataLenght;
	int timeout = SendDataTimeout;
	static unsigned int __stdcall ServClient(void *data);
	int sendData(std::string data);
	static int sendData(SOCKET s, std::string data);
	std::string receiveData(int timeout);
	static std::string receiveData(SOCKET s, int timeout);
	static void closeSocket();
	static void closeSocket(SOCKET s);
};