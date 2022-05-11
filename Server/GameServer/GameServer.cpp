﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<atomic>
#include <mutex>
#include<windows.h>
#include<future>

//_declspec(thread) int32 value;
thread_local int32 LThreadId = 0;

void ThreadMain(int32 threadId)
{
	LThreadId = threadId;

	while (true)
	{
		cout << "Hi! I am Thread " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}

int main()
{
	vector<thread> threads;

	for (int32 i = 0; i < 10; i++)
	{
		int32 threadid = i + 1;
		threads.push_back(thread(ThreadMain, threadid));
	}

	for (thread& t : threads)
	{
		t.join();
	}

	return 0;
}