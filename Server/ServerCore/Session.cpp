#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "Service.h"

/*--------------
	Session
---------------*/

Session::Session()
{
	_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(_socket);
}

void Session::Disconnect(const WCHAR* cause)
{

}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	// TODO
}

void Session::RegisterConnect()
{

}

void Session::RegisterRecv()
{
	if (IsConnected() == false)
		return;

	//RecvEvent

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer);
	wsaBuf.len = len32(_recvBuffer);

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, OUT & flags, &);
}

void Session::RegisterSend()
{

}

void Session::ProcessConnect()
{
	_connected.store(true);

	GetService()->AddSession(GetSessionRef());

	OnConnected();

	RegisterRecv();

}

void Session::ProcessRecv(int32 numOfBytes)
{

}

void Session::ProcessSend(int32 numOfBytes)
{

}

void Session::HandleError(int32 errorCode)
{

}