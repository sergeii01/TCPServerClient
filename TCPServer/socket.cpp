#include "socket.h"


Ssocket::Ssocket()
{
	addr.sin_family = AF_INET;
}

Ssocket::~Ssocket()
{
}

int Ssocket::runServer(string serverIP, int serverPORT)
{
	setServerIPstr(serverIP);
	setServerPORTstr(serverPORT);
	if (setWSA() != 0)
	{
		cout << "WSA startup failed" << endl;
		return 1;
	}
	else
		cout << "WSA startup OK" << endl;
	if (createSock() != 0)
	{
		cout << "Invalid socket" << endl;
		return 2;
	}
	else
		cout << "Socket OK" << endl;

	if (bindServer() != 0)
	{
		cout << "Bind failed" << GetLastError() << endl;
		return 3;
	}
	else
		cout << "Bind OK" << endl;
	if (listServer() != 0)
	{
		cout << "List failed" << GetLastError() << endl;
		return 4;
	}
	else 
		cout << "Listen OK and waiting connection" << endl;

	//while (client = accept(sock, 0, 0))
	while (client2.client = accept(sock, 0, 0))
	{
		//if (client == INVALID_SOCKET)
		if (client2.client == INVALID_SOCKET)
		{
			cout << "Invalid client socket" << GetLastError() <<endl;
			continue;
		}
		client2.pwd = pg.getNextPWD();
		//HANDLE h = (HANDLE) _beginthreadex(0, 0, ServClient, (void*)&client, 0, 0);
		HANDLE h = (HANDLE)_beginthreadex(0, 0, ServClient, (void*)&client2, 0, 0);
		CloseHandle(h);

	}
	return 0;
}

int Ssocket::connectClient(string serverIP, int serverPORT)
{
	setServerIPstr(serverIP);
	setServerPORTstr(serverPORT);
	if (setWSA() != 0)
	{
		cout << "WSA startup failed" << endl;
		return 1;
	}
	else
		cout << "WSA startup OK" << endl;
	if (createSock() != 0)
	{
		cout << "Invalid socket" << endl;
		return 2;
	}
	else
		cout << "Socket OK" << endl;
	if (connectToServer() != 0)
	{
		cout << "Connection error" << endl;
		return 2;
	}
	else
		cout << "Connection OK" << endl;
	return 0;
}

string Ssocket::getServerIPstr()
{
	return string();
}

string Ssocket::getServerPORTstr()
{
	return string();
}

SOCKET * Ssocket::getSock()
{
	SOCKET * ptrSock;
	ptrSock = &sock;
	return ptrSock;
}

unsigned int Ssocket::ServClient(void * data)
{
	//SOCKET Client = *((SOCKET*)data);
	SockAccept Client = *((SockAccept*)data);
	cout << "Client connected" << endl;

	char chunk[200];
	while (recv(Client.client, chunk, 200, 0))
	{
		//printf("%s \t %d\n", chunk, GetCurrentThreadId());
		cout << chunk << "\t" << Client.pwd << "\t" << GetCurrentThreadId() << endl;
		Sleep(50);// < chunk << "\t" << GetCurrentThreadId() << endl;
	}
	cout << "end connection" << endl;
	closesocket(Client.client);
	
	//_endthreadex(0);
	return 0;
}


int Ssocket::setServerIPstr(string serverIP)
{
	addr.sin_addr.S_un.S_addr = inet_addr(serverIP.c_str());
	return 0;
}

int Ssocket::setServerPORTstr(int serverPORT)
{
	addr.sin_port = htons(serverPORT);
	return 0;
}

int Ssocket::setWSA()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);//2.2 
	if (iResult)
	{
		return 1;
	}
	return 0;
}

int Ssocket::createSock()
{

	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock == INVALID_SOCKET)
	{
		return 2;
	}
	
	return 0;
}

int Ssocket::bindServer()
{
	int iResult = bind(sock, (sockaddr*)&addr, sizeof(sockaddr_in));
	if (iResult)
	{
		return 1;
	}
	return 0;
}

int Ssocket::listServer()
{
	int iResult = listen(sock, SOMAXCONN);
	if (iResult)
	{
		return 1;
	}
	return 0;
}

int Ssocket::connectToServer()
{
	int iResult = connect(sock, (SOCKADDR*)&addr, sizeof(sockaddr_in));
	if (iResult)
	{
		printf("Connect failed %u", WSAGetLastError());
		return 1;
	}

	return 0;
}
