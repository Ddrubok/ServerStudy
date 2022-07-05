#pragma once
#include "Job.h"
class Room
{
public:
	void Enter(PlayerRef player);
	void Leave(PlayerRef player);
	void Broadcast(SendBufferRef sendBuffer);

private:
	USE_LOCK;
	map<uint64, PlayerRef> _players;

	JobQueue _jobs;
};

extern Room GRoom;

class EnterJob : public IJob
{
	EnterJob(Room& room, PlayerRef player) :_room(room),_player(player)
	{

	}

	virtual void Execute()override
	{
		_room.Enter(_player);
	}

public:
	Room& _room;
	PlayerRef _player;
};
