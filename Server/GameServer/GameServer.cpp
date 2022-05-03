// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"

#include<thread>
#include<atomic>

// atomic atom(원자)
// All-Or_Nothing
//DB
atomic<int32> sum = 0;

void Add()
{
	for (int32 i = 0; i < 1000000; i++)
	{
		//sum++;
		sum.fetch_add(1);
	}
}


void Sub()
{
	for (int32 i = 0; i < 1000000; i++)
	{
		//sum--;
		sum.fetch_add(-1);
	}
}

int main()
{

	std::thread t1(Add);
	std::thread t2(Sub);

	if (true == t1.joinable())
		t1.join();

	if (true == t2.joinable())
		t2.join();

	cout << sum << endl;

	return 0;
}