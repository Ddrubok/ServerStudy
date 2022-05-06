// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<thread>
#include<atomic>
#include <mutex>
#include"AccountManger.h"
#include "UserManger.h"

void Fun1()
{
	for (int i = 0; i < 100; i++)
	{
		UserManger::Instance()->ProcessSave();
	}
}


void Fun2()
{
	for (int i = 0; i < 100; i++)
	{
		AccountManger::Instance()->ProcessLogin();
	}
}

int main()
{
	std::thread t1(Fun1);
	std::thread t2(Fun2);

	t1.join();
	t2.join();
	cout << "Jobs Done" << endl;

	mutex m1,m2;

	std::lock(m1, m2);

	lock_guard<mutex> g1(m1, std::adopt_lock);
	lock_guard<mutex> g2(m2, std::adopt_lock);

	return 0;
}