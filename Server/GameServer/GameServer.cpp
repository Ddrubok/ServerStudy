﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"

#include<thread>
#include<atomic>
#include <mutex>

// atomic atom(원자)
// All-Or_Nothing
//DB
vector<int> v;

//Mutual Exclusive (상호배타적)
mutex m;

template<typename T>
class LockGuard
{
public:
	LockGuard(T& m)
	{
		_mutex = &m;
		_mutex->lock();
	}
	~LockGuard()
	{
		_mutex->unlock();
	}

private:
	T* _mutex;
};

//재귀적으로 lock을 할 수 있는것이 큰 게임에서 유리하다.

void Push()
{
	for (int32 i = 0; i < 100000; i++)
	{
		// Lock()은 한 스레드가 접근했을 때 다른 스레드의 접근을 막는다.?
		//unlock()다른 스레드의 접근을 허용한다

		LockGuard<std::mutex> d(m);
		v.push_back(i);

		
		
	}
}



int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	if (t1.joinable())
		t1.join();

	if (t2.joinable())
		t2.join();

	cout << v.size() << endl;

	return 0;
}