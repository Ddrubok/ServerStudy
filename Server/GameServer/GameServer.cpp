#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include <atomic>
#include <mutex>
#include <windows.h>
#include <future>
#include "ThreadManager.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void HandleError(const char* cause)
{
	int32 errCode = ::WSAGetLastError();
	cout << cause << " ErrorCode : " << errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		HandleError("Socket");
		return 0;
	}

	bool enable = true;

	::setsockopt(serverSocket,SOL_SOCKET,SO_KEEPALIVE,(char*)&enable, sizeof(enable));

	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 5;


	::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)&linger, sizeof(linger));


	shutdown(serverSocket,SD_SEND);


	//SO_SNDBUF = 송신 버퍼 크기
	//SO_RCVBUF = 수신 버퍼 크기

	int32 sendBufferSize;
	int32 optionLen = sizeof(sendBufferSize);



	::getsockopt(serverSocket,SOL_SOCKET,SO_SNDBUF,(char*)&sendBufferSize,&optionLen);

	cout << "송신 버퍼 크기: " << sendBufferSize << endl;

	int32 recvBufferSize;
	optionLen = sizeof(recvBufferSize);

	::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)&recvBufferSize, &optionLen);

	cout << "수신 버퍼 크기: " << recvBufferSize << endl;

	//SO_REUSEADDR
	//IP주소 및 port 재사용

	{
		bool enable = true;
		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&enable, sizeof(enable));
	}

	//IPPROTO_TCP
	//TCP_NODELAY =Nagle 네이글 알고리즘 작동여부
	//데이터가 충분히 크면 보내고 그렇지 않으면 데이터가 충분히 쌓일때까지 대기!
	//장점 : 작은 패킷이 불필요하게 많이 생성되는 일을 방지
	//단점 : 반응 시간 손해

	{
		bool enalbe = true;
		::setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&enable, sizeof(enable));
	}


	closesocket(serverSocket);

	// 윈속 종료
	::WSACleanup();
}