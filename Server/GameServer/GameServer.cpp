#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 0;
	}

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);

	if (listenSocket == INVALID_SOCKET)
	{
		int errCode = ::WSAGetLastError();
		cout << "Socket ErrorCode: " << errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);// 알아서 해줌
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int errCode = ::WSAGetLastError();
		cout << "Bind ErrorCode: " << errCode << endl;
		return 0;
	}

	if (::listen(listenSocket, 10) == SOCKET_ERROR)
	{
		int errCode = ::WSAGetLastError();
		cout << "Listen ErrorCode: " << errCode << endl;
		return 0;
	}

	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		SOCKET clientSocekt = ::accept(listenSocket, (SOCKADDR*)&clientAddr,&addrLen);
		if (clientSocekt == INVALID_SOCKET)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Accept ErrorCode: " << errCode << endl;
			return 0;
		}
		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "Client Connect! IP= " << ipAddress << endl;


		while (true)
		{
			char recvBuffer[1000];
			int32 recvLen = ::recv(clientSocekt, recvBuffer, sizeof(recvBuffer), 0);

			if (recvLen <= 0)
			{
				int errCode = ::WSAGetLastError();
				cout << "Recv ErrorCode: " << errCode << endl;
				return 0;
			}

			cout << "Recv Data! Data = " << recvBuffer << endl;
			cout << "Recv Data! Len = " << recvLen << endl;

			int32 resultCode = ::send(clientSocekt, recvBuffer, sizeof(recvBuffer), 0);

			if (resultCode == SOCKET_ERROR)
			{
				int errCode = ::WSAGetLastError();
				cout << "Send ErrorCode: " << errCode << endl;
				return 0;
			}
		}
	}
	//윈도우 소켓 종료
	::WSACleanup();
}