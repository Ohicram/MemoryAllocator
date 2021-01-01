#pragma once

#include <memory>

class Mallocator
{
public:
	void* allocate(size_t size)
	{
		return malloc(size);
	}

	void deallocate(void* mem_ptr, size_t size = 0)
	{
		if (mem_ptr != nullptr)
			free(mem_ptr);
	}

	bool owns(void* mem_ptr)
	{
		// @todo: boh...
		return mem_ptr != nullptr;
	}
};