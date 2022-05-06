#include "pch.h"
#include "UserManger.h"
#include "AccountManger.h"

void UserManger::ProcessSave()
{
	Account* account = AccountManger::Instance()->GetAccount(100);
	lock_guard<mutex> guard(_mutex);

	
}
