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

const int32 BUFSIZE = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BUFSIZE] = {};
	int32 recvBytes = 0;
	WSAOVERLAPPED overlapped = {};
};

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//블로킹 소켓
	//accept->접속한 클라가 있을 때
	//connect -> 서버 접속 성공했을때
	//send, sendto ->요청한 데이터를 송신 버퍼에 복사했을 때
	//recv, recvform ->수신 버퍼에 도착한 데이터가 있고 이를 유저레벨 버퍼에 복사 했을 때

	//논 블로킹 소켓(Non-Blocking)
	//

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;


	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	cout << "Accept" << endl;

	//Overlapped IO(비동기 + 논블로킹)
	//Overlapped 함수 건다
	//Overlapped함수 성공 여부 확인
	//성공했다면 결과 얻어서 처리
	//실패했다면 사유를 확인




	//1)비동기 입출력 소켓 넣기
	//2)WSABUF 배열의 시작 주소 + 개수
	//3)보내고/받은 바이트 수
	//4) 상세 옵션인데 0
	//5) WSAOVERLAPPED 구조체 주소값
	//6) 입출력이 완료되면 OS가 호출할 콜백 함수
	//WSASend
	//WSARecv

	//Overlapped 모델 (이벤트 기반)
	//-비동기 입출력 지원하는 소켓 생성 + 통지 받기 위한 이벤트 객체 생성
	//-비동기 입출력 함수 호출 (1에서 만든 이벤트 객체를 같이 넘겨줌)
	//-비동기 작업이 바로 완료되지 않으면 , WSA_IO_PENDING 오류 코드
	//운영체제는 이벤트 객체를 signaled 상태로 만들어서 완료 상태 알려줌

	while (true)
	{
		SOCKADDR_IN clientAddr;
		SOCKET clientSocket;
		int32 addrLen = sizeof(clientSocket);


		while (true)
		{
			clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientSocket, &addrLen);
			if (clientSocket != INVALID_SOCKET)
				break;

			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			return 0;
		}

		Session session = Session{ clientSocket };
		WSAEVENT wsaEvent = ::WSACreateEvent();
		session.overlapped.hEvent = wsaEvent;

		cout << "Client Connected! " << endl;

		while (true)
		{
			WSABUF wsaBuf;
			wsaBuf.buf = session.recvBuffer; // recvBuffer 절대 건들이지 마라.
			wsaBuf.len = BUFSIZE;

			DWORD recvLen = 0;
			DWORD flags = 0;

			if (::WSARecv(clientSocket, &wsaBuf, 1, &recvLen, &flags, &session.overlapped, nullptr) == SOCKET_ERROR)
			{
				if (::WSAGetLastError() == WSA_IO_PENDING)
				{
					//Pendding
					::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
					::WSAGetOverlappedResult(session.socket, &session.overlapped, &recvLen, FALSE, &flags);
				}
				else
				{
					break;
				}
			}

			cout << "Data Recv Len = " << recvLen << endl;
		}

		::closesocket(session.socket);
		::WSACloseEvent(wsaEvent);
	}

	// 윈속 종료
	::WSACleanup();
}