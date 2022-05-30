#pragma once
class BaseAllocator
{
public:
	static void* Allock(int32 size);
	static void Release(void* ptr);
};

