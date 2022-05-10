﻿// GameServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "Pch.h"
#include <iostream>
#include "CorePch.h"
#include<atomic>
#include <mutex>
#include<windows.h>
#include<future>

atomic<bool> ready;
int32 value;

void Producer()
{
	value = 10;

	ready.store(true, memory_order::memory_order_seq_cst);
}

void Consumer()
{
	while (ready.load(memory_order::memory_order_seq_cst) == false)
		;

	cout << value << endl;
}

int main()
{
	ready = false;
	value = 0;
	thread t1(Producer);
	thread t2(Consumer);
	t1.join();
	t2.join();
	// Memory Model(정책)
	//1) Sequentially Consistent (seq_cst)
	//2)Acquire)Release(acquire,release)
	//3)Relaxed(relaxed)

	//1)seq_cst(가장엄격 = 컴파일러 최적화 여지 적음 = 직관적)//
	// 가시성 문제 바로 해결, 코드재배치도 해결!
	// 
	//2)acquire-release
	// 딱중간
	// release 명령 이전의 메모리 명령들이 해당 명령 이후로 재배치 되는 것을 금지
	// 그리고 acquire로 같은 변수를 읽는 쓰레드가 있다면
	// release 이전의 명령들이 -> acquire 하는 순간에 관찰 가능
	// 
	//3)relaxed(자유롭다 = 컴파일러 최적화 여지 많음 = 직관적이지 않음)
	//자율성 높음
	//코드재비치도 가능 = 가시성 해결 x
	//기본 조건만 가능 (동일객체에 대한 동일 관전 순서만 보장)

	//인텔, amd의 경우 애당초 순차적 일관성을 보장을 해서 , seq_cst를 써도 별다른 부하가없음
	//ARM의 경우 꽤 차이가 있다.
}