#pragma once

template<size_t threshold, class SmallAllocator, class LargeAllocator>
class SegregatorAllocator : private SmallAllocator, private LargeAllocator
{
public:
	void* allocate(size_t size)
	{
		if (size > threshold)
			return LargeAllocator::allocate(size);
		else
			return SmallAllocator::allocate(size);
	}

	void deallocate(void* mem_ptr, size_t size = 0)
	{
		if (size > threshold)
			return LargeAllocator::deallocate(mem_ptr, size);
		else
			return SmallAllocator::deallocate(mem_ptr, size);
	}

	bool owns(void* mem_ptr)
	{
		return LargeAllocator::owns(mem_ptr) || SmallAllocator::owns(mem_ptr);
	}
};