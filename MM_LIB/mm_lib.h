#pragma once

#include "Private/mm_allocation.h"

namespace mm_stats
{
	size_t GetAllocatedMemory();
}


//#define MM_LIB_DISABLE

#ifndef MM_LIB_DISABLE

void* operator new(size_t size);
void* operator new[](size_t size);
void operator delete(void* memory);
void operator delete[](void* memory);

#endif


