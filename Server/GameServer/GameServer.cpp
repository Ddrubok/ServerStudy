﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<thread>
#include<atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q; 

//cv는 Uswer- Level Object(커널 오브젝트x)
condition_variable cv;

void Producer()
{
	//1) Lock을 잡고
	//2) 공유 변수 값을 수정
	//3) lock을 풀고
	//4) 조건변수 통해 다른 쓰레드 공지

	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		cv.notify_one(); // wait중인 쓰레드가 있으면 단 1개를 깨운다.
	}
}

void Consumer()
{
	while (true)
	{

		unique_lock<mutex> lock(m);
		cv.wait(lock, []() {return q.empty() == false; });

		//1) lock을 잡고
		//2) 조건을 확인
		// - 만족 -> 빠져 나와서 이어서 코드를 진행
		//- 불만족 -> lock을 풀어주고 대기 상태.

		//그런데 notify_one을 했으면 항상 조건식을 만족하는거 아닐까?
		//Spurious Wakeup( 가짜기상)
		//notify_one 할 때 lock을 잡고 있는 것이 아니기 때문에

		//::ResetEvent(handle);

		//if (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
	
}

int main()
{

	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}