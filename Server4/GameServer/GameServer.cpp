#include "pch.h"
#include "ThreadManager.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include <tchar.h>
#include "Protocol.pb.h"
#include "Job.h"
#include "Room.h"
#include "Player.h"
#include <functional>

void HelloWorld(int32 a, int32 b)
{
	std::cout << "hello world" << std::endl;
}

class Knight : public enable_shared_from_this<Knight>
{
public:
	void HealMe(int32 value)
	{
		_hp += value;
		cout << "HealMe! " << value << endl;
	}

	void Test()
	{
		auto job = [self = shared_from_this()]()
		{
			self->HealMe(self->_hp);
		};
	}

private:
	int32 _hp = 100;
};

int main()
{
	PlayerRef player = make_shared<Player>();
	std::function<void(void)> func = [self= GRoom,&player]()
	{
		HelloWorld(1, 2);
		self->Enter(player);
	};


	func();

	ClientPacketHandler::Init();

	ServerServiceRef service = MakeShared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>, 		100);

	ASSERT_CRASH(service->Start());

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}				
			});
	}	

	while (true)
	{
		GRoom->FlushJob();
		this_thread::sleep_for(1ms);
	}

	GThreadManager->Join();
}