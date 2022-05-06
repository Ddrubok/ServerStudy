#include "pch.h"
#include "AccountManger.h"
#include "UserManger.h"


void AccountManger::ProcessLogin()
{
	lock_guard<mutex> guard(_mutex);
	User* user = UserManger::Instance()->GetUser(100);
}