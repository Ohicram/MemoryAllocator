#pragma once

template<size_t threshold, class SmallAllocator, class LargeAllocator>
class SegregatorAllocator
{
	SmallAllocator m_small;
	LargeAllocator m_large;
public:
	void* allocate(size_t size)
	{
		if (size > threshold)
			return m_large.allocate(size);
		else
			return m_small.allocate(size);
	}

	void deallocate(void* mem_ptr, size_t size = 0)
	{
		if (size > threshold)
			return m_large.deallocate(mem_ptr, size);
		else
			return m_small.deallocate(mem_ptr, size);
	}

	bool owns(void* mem_ptr)
	{
		return m_large.owns(mem_ptr) || m_small.owns(mem_ptr);
	}
};