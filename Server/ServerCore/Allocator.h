#pragma once
class BaseAllocator
{
public:
	static void* Allock(int32 size);
	static void Release(void* ptr);
};

class StompAllocator
{
	enum{PAGE_SIZE =0x1000};
public:
	static void* Allock(int32 size);
	static void Release(void* ptr);
};

