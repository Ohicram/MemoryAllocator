#include "mm_lib.h"
#include <iostream>
#include "Private/FallbackAllocator.h"
#include "Private/Mallocator.h"
#include "Private/SegregatorAllocator.h"
#include "Private/SmallAllocator.h"
#include "Private/StackAllocator.h"

static size_t alloc_mem = 0;

size_t mm_stats::GetAllocatedMemory()
{	
	return alloc_mem;
}

//static StackAllocator<16384> s_ChunkAlloc;
//static SegregatorAllocator<16, SmallAllocator<16, 128>, Mallocator> s_Allocator;
static FallbackAllocator<SegregatorAllocator<16, SmallAllocator<16, 128>, StackAllocator<512>>, Mallocator> s_Allocator;

#ifndef MM_LIB_DISABLE

void* operator new(size_t size)
{
	void* ptr = s_Allocator.allocate(size);
	if(ptr)
	{
		alloc_mem += size;
	}
	return ptr;
}

void* operator new[](size_t size)
{
	void* ptr = s_Allocator.allocate(size);
		if (ptr)
		{
			alloc_mem += size;
		}
	return ptr;
}

void operator delete(void* memory)
{
	if(memory)
	{
		alloc_mem -= 1;// _msize(memory);
		s_Allocator.deallocate(memory, 1);// _msize(memory));
	}
}

void operator delete[](void* memory)
{
	if (memory)
	{
		alloc_mem -= _msize(memory);
		s_Allocator.deallocate(memory, _msize(memory));
	}
}

#endif
