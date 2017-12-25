#include "socket.h"

SOCKET Ssocket::sock = NULL;

Ssocket::Ssocket()
{
	addr.sin_family = AF_INET;
	::InitializeCriticalSection(&lock);
}

Ssocket::~Ssocket()
{
	::DeleteCriticalSection(&lock);
}

int Ssocket::runServer(std::string serverIP, int serverPORT)
{
	SOCKET cl;
	
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
	//while (client2.client = accept(sock, 0, 0))
	while (cl = accept(sock, 0, 0))
	{
		if (cl == INVALID_SOCKET)
		{
			cout << "Invalid client socket" << GetLastError() << endl;
			continue;
		}
		//EnterCriticalSection(&lock);
		Connection* conn = new Connection(cl);		
		//conn->setPassword(pg.getNextPWD(10));
		conn->setPassword("aaaaaa");
		//LeaveCriticalSection(&lock);

		HANDLE h = (HANDLE)_beginthreadex(0, 0, ServClient, conn, 0, 0);    
		CloseHandle(h);
		cout << ".";
	}
	return 0;
}

int Ssocket::connectClient(std::string serverIP, int serverPORT)
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

std::string Ssocket::getServerIPstr()
{
	return string();
}

std::string Ssocket::getServerPORTstr()
{
	return string();
}

//SOCKET * Ssocket::getSock()
//{
//	SOCKET * ptrSock;
//	ptrSock = &sock;
//	return ptrSock;
//}

unsigned int __stdcall Ssocket::ServClient(void* data)
{
	Connection* conn=NULL;
	char ptr[100] = "TEST STRING";
	char inptr[100];
	try
	{
		Connection* conn = ((Connection*)data);
		//cout << "Client connected" << endl;
		if (conn)
		{
			SOCKET s = conn->getSocket();
			send(s, ptr, sizeof(ptr), 0); 
			Sleep(20);
			recv(s, inptr, 100, 0);
			Sleep(20);
			shutdown(s, SD_BOTH);
			closesocket(s);
			delete conn;
		}
		
		
		

		//sprintf(ptr, to_string(s).c_str(), '\t', data.c_str());
		

		

		/*if (send(s, ptr, sizeof(ptr), 0) != 100)
		{
			cout << endl << "NEDOSLALI" << endl;
			return 1;
		}*/

		//Sleep(20);
		//if (sendData(conn->getSocket(), conn->getPassword()) != 0)
		//	;// Sleep(200);

		//string ats = "";
		//receiveData(conn->getSocket(), 200);

	}
	catch(...)
	{
		cout << "!!!!!!!!!!EXCEPTION!!!!!!!!!!!! \t" << GetLastError() << "\t"<<WSAGetLastError()<< endl;
	}
	if (conn)
	{
		conn->closeSocket();
		delete conn;
	}	
	return 0;
}

int Ssocket::sendData(std::string data)
{

	char ptr[100];
	sprintf(ptr, data.c_str());
	Sleep(200);
	if (send(sock, ptr, sizeof(ptr), 0))
		return 0;
	else
		return 1;
}

int Ssocket::sendData(SOCKET s, std::string data)
{
	char ptr[100];
	
	sprintf(ptr, to_string(s).c_str(), '\t' ,data.c_str());
	Sleep(200);
	if (send(s, ptr, sizeof(ptr), 0) != 100)
	{
		cout << endl << "NEDOSLALI" << endl;
		return 1;
	}
	
	return 0;
}

std::string Ssocket::receiveData(int timeout)
{
//	SockAccept Client = *((SockAccept*)data);
//	cout << "Client connected" << endl;

	char chunk[200];
	while (recv(sock, chunk, 200, 0))
	{
		cout << chunk << "\t" /*<< Client.pwd << "\t" << GetCurrentThreadId()*/ << endl;
		Sleep(timeout);
		break;
	}
	//cout << "end connection" << endl;
	return std::string(chunk);
}

std::string Ssocket::receiveData(SOCKET s, int timeout)
{
	char chunk[200];
	int check = 0;
	//while (recv(s, chunk, 200, 0)) 
	//do
	//{
		check = recv(s, chunk, 200, 0);
		if(check != 100)
			cout << endl << "NEDOPOLUCHILI" << endl;
		//cout << chunk << "XXXX\t" /*<< Client.pwd << "\t" << GetCurrentThreadId()*/ << check << '\t' << GetLastError() << "\t" << endl;
		/*if (GetLastError() != 0)
		{
			closeSocket(s);
			check = 1;
		}*/
		Sleep(timeout);

	//} while (check < 0);
	return std::string(chunk);
}

void Ssocket::closeSocket()
{
	shutdown(sock, SD_BOTH);
	closesocket(sock);
}

void Ssocket::closeSocket(SOCKET s)
{

	shutdown(s, SD_BOTH);
	closesocket(s);
}


int Ssocket::setServerIPstr(std::string serverIP)
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
	
	char enable = '1';

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
		//error("setsockopt(SO_REUSEADDR) failed");
		return 3;

	linger lin;
	unsigned int y = sizeof(lin);
	lin.l_onoff = 1;
	lin.l_linger = 0;
	if (setsockopt(sock, SOL_SOCKET, SO_LINGER, (char *)(&lin), y) < 0)
		return 4;

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

void Connection::closeSocket()
{
	if (m_sock)
	{
		shutdown(m_sock, SD_BOTH);
		closesocket(m_sock);
	}	
}

Connection::Connection(SOCKET s)
{
	m_sock = s;
}

Connection::~Connection()
{
	closeSocket();
}

void Connection::setPassword(std::string pw)
{
	m_pwd = pw;
}

std::string Connection::getPassword()
{
	return m_pwd;
}

SOCKET Connection::getSocket()
{
	return m_sock;
}
