#include "mm_lib.h"
#include <iostream>
#include "Private/ChunkAllocator.h"
#include "Private/FixedSizeAllocator.h"
#include "Private/Mallocator.h"
#include "Private/SmallAllocator.h"

static size_t alloc_mem = 0;

size_t mm_stats::GetAllocatedMemory()
{	
	return alloc_mem;
}

static SmallAllocator<16, 128> s_ChunkAlloc;


#ifndef MM_LIB_DISABLE

void* operator new(size_t size)
{
	void* ptr = s_ChunkAlloc.allocate(size);
	if(ptr)
	{
		alloc_mem += size;
	}
	return ptr;
}

void* operator new[](size_t size)
{
	void* ptr = s_ChunkAlloc.allocate(size);
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
		s_ChunkAlloc.deallocate(memory, 1);// _msize(memory));
	}
}

void operator delete[](void* memory)
{
	if (memory)
	{
		alloc_mem -= _msize(memory);
		s_ChunkAlloc.deallocate(memory, _msize(memory));
	}
}

#endif
