#pragma once
#include <mutex>

class User 
{

};

class UserManger
{
public:
	static UserManger* Instance()
	{
		static UserManger instance;
		return &instance;
	}

	User* GetUser(int32 id)
	{
		lock_guard<mutex> guard(_mutex);
		return nullptr;
	}
	void ProcessSave();

private:
	mutex _mutex;
};

