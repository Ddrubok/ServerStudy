#pragma once
#include <mutex>

class Account
{

};


class AccountManger
{
public:
	static AccountManger* Instance()
	{
		static AccountManger instance;
		return &instance;
	}

	Account* GetAccount(int32 id)
	{
		lock_guard<mutex> guard(_mutex);
		return nullptr;

	}

	void ProcessLogin();

private:
	mutex _mutex;
};

