#pragma once

#include <memory>

class Mallocator
{
	void* allocate(size_t size)
	{
		return malloc(size);
	}

	void free(void* mem_ptr, size_t size = 0)
	{
		if (mem_ptr != nullptr)
			free(mem_ptr);
	}
};