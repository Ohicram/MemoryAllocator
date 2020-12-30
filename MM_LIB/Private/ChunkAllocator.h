#pragma once
#include <memory>

template<size_t BlockSize, uint8_t Blocks>
class ChunkAllocator
{
public:
	ChunkAllocator()
	{
		//chunk_ptr = (uint8_t*) malloc(Blocks * BlockSize);
		free_blk_pos = 0;

		uint8_t idx = 0;
		for (uint8_t* p = chunk_ptr; p < (chunk_ptr + BlockSize * Blocks); p += BlockSize) {
			*p = ++idx;
		}
	}
	~ChunkAllocator()
	{
		//free(chunk_ptr);
	}
	ChunkAllocator(const ChunkAllocator& other) = delete;
	//ChunkAllocator(ChunkAllocator&& other) = default;
	ChunkAllocator& operator=(const ChunkAllocator& other) = delete;
	//ChunkAllocator& operator=(ChunkAllocator&& other) = default;

	void* allocate(size_t size)
	{
		if ( (chunk_ptr + free_blk_pos) < (chunk_ptr + BlockSize * Blocks))
		{
			uint8_t* blk_ptr = chunk_ptr + free_blk_pos;
			free_blk_pos = *blk_ptr;
			return blk_ptr;
		}
		return nullptr;
	}

	bool owns(void* mem_ptr)
	{
		return mem_ptr >= chunk_ptr && mem_ptr < (chunk_ptr + BlockSize * Blocks);
	}
	
	void deallocate(void* mem_ptr, size_t size)
	{
		if (owns(mem_ptr))
		{
			*((uint8_t*)mem_ptr) = free_blk_pos;
			free_blk_pos = (((uint8_t*)mem_ptr) - chunk_ptr);
		}
	}
private:
	uint8_t chunk_ptr[BlockSize * Blocks];
	uint8_t free_blk_pos = 0;
};
