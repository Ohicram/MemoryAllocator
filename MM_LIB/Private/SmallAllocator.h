#pragma once

#include <algorithm>
#include <array>
#include <utility>

#include "ChunkAllocator.h"
#include "FixedSizeAllocator.h"


template <uint8_t ChunkSize, std::size_t... Is>
std::array<IFixedSizeAllocator*, sizeof...(Is)> makeInterfaceArray(std::index_sequence<Is...>)
{
	static std::tuple< FixedSizeAllocator<ChunkAllocator<Is+1, ChunkSize / (Is+1)>, Is+1> ...> data{};
	return { { &std::get<Is>(data)... } };
}

template <uint8_t ChunkSize, std::size_t N>
std::array<IFixedSizeAllocator*, N> makeInterfaceArray()
{
	return makeInterfaceArray<ChunkSize>(std::make_index_sequence<N>{});
}

template<uint8_t MaxObjSize, uint8_t ChunkSize>
class SmallAllocator
{
public:
	SmallAllocator()
	{
		size_t i = 0;
		for (IFixedSizeAllocator* ptr : makeInterfaceArray<ChunkSize, MaxObjSize>())
		{
			m_pool[i++] = ptr;
		}
	}
	
	void* allocate(size_t size)
	{
		if (size < MaxObjSize)
			return m_pool[size - 1]->allocate(size);
		return nullptr;
	}
	
	void deallocate(void* mem_ptr, size_t size)
	{
		if (size < MaxObjSize)
			m_pool[size - 1]->deallocate(mem_ptr, size);
	}

	bool owns(void* mem_ptr)
	{
		for (size_t i = 0; i < MaxObjSize; ++i)
		{
			if (m_pool[i]->owns(mem_ptr))
				return true;
		}
		return false;
	}
private:
	IFixedSizeAllocator* m_pool[MaxObjSize];
};
