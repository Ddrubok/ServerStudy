﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<thread>
#include<atomic>
#include <mutex>


class Spinlock
{
public:
	void lock()
	{
		//CAS (Compare-And-Swap)

		bool expected = false;
		bool desired = true;

		//CAS의사코드
		/*if (_locked == expected)
		{
			expected = _locked;
			_locked = desired;
			return true;
		}
		else
		{
			expected = _locked;
			return false;
		}*/

		

		while (_locked.compare_exchange_strong(expected,desired)==false)
		{
			expected = false;
		}
	}

	void unlock()
	{
		_locked.store(false);
	}

private:
	atomic<bool> _locked = false;
};

//volatile 최적화 하지마라

int32 sum = 0;

mutex m;

Spinlock spinlock;

void Add()
{
	for (int32 i = 0; i < 100000; i++)
	{
		lock_guard<Spinlock> guard(spinlock);
		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 100000; i++)
	{
		lock_guard<Spinlock> guard(spinlock);
		sum--;
	}
}


int main()
{
	thread t1(Add);
	thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum;

	return 0;
}