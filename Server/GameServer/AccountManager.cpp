#include "pch.h"
#include "AccountManager.h"
#include"PlayerManager.h"

AccountManager GAccountManager;

void AccountManager::AccountThenPlyer()
{
	Write_LOCK;
	GPlayerManager.Lock();
}

void AccountManager::Lock()
{
	Write_LOCK;
}
