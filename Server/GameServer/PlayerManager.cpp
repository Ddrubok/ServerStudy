#include "pch.h"
#include "PlayerManager.h"
#include "AccountManager.h"

PlayerManager GPlayerManager;

void PlayerManager::PlayerThenAccount()
{
	Write_LOCK;
	GAccountManager.Lock();

}

void PlayerManager::Lock()
{
	Write_LOCK;
}
