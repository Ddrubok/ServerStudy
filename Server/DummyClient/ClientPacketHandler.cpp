#include "pch.h"
#include "ClientPacketHandler.h"
#include <BufferReader.h>

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	switch (header.id)
	{
	case S_TEST:
		Handle_S_TEST(buffer, len);
		break;
	}


}

struct S_TEST
{
	uint64 id;
	uint32 hp;
	uint16 attack;
};

void ClientPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	uint64 id;
	uint32 hp;
	uint16 attack;

	br >> id >> hp >> attack;

	cout << "ID: " << id << " HP: " << hp << " Attack: " << attack << endl;
}
