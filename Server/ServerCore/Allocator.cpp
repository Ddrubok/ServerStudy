#include "pch.h"
#include "Allocator.h"

void* BaseAllocator::Allock(int32 size)
{
	return ::malloc(size);
}

void BaseAllocator::Release(void* ptr)
{
	::free(ptr);
}
