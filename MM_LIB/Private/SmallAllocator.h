#pragma once

#include <vector>

template<uint8_t MaxObjSize, uint8_t ChunkSize>
class SmallAllocator
{
public:
	SmallAllocator()
	{
		// We want to have a collection of fixed size allocators.
		// Each FSA can allocate a different number of blocks depending on its size
		for (size_t i = 1; i < MaxObjSize; ++i) {
			uint8_t n_blocks = ChunkSize / i;
			m_pool.emplace_back(i, n_blocks);
		}
	}
	
	void* allocate(size_t size)
	{
		if (size < MaxObjSize)
			return m_pool[numBytes - 1].allocate();
		return nullptr;
	}
	
	void deallocate(void* mem_ptr, size_t size)
	{
		if (size < MaxObjSize)
			m_pool[size - 1].deallocate();
	}
private:
	std::vector<FixedSizeAllocator> m_pool;
};
