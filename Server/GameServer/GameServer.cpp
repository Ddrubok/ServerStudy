﻿#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<atomic>
#include <mutex>
#include<windows.h>
#include<future>
#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

LockQueue<int32> q;
LockFreeStack<int32> s;

void Push()
{
	while (true)
	{

		int32 value = rand() % 100;
		s.Push(value);

		this_thread::sleep_for(10ms);
	}
}

void Pop()
{
	while (true)
	{

		int32 data = 0;
		if (s.TryPop(OUT data))
			cout << data << endl;
	}
}


int main()
{
	thread t1(Push);
	thread t2(Pop);
	thread t3(Pop);

	t1.join();
	t2.join();
	t3.join();
	return 0;
}