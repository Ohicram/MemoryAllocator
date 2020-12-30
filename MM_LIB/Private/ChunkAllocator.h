#pragma once
#include <cstring>
#include <memory>

template<size_t BlockSize, uint8_t Blocks>
class ChunkAllocator
{
public:
	ChunkAllocator()
	{
		chunk_ptr = (uint8_t*) malloc(Blocks * BlockSize);
		free_blk_pos = 0;
		free_blocks = Blocks;
		uint8_t idx = 0;
		for (uint8_t* p = chunk_ptr; p < (chunk_ptr + BlockSize * Blocks); p += BlockSize) {
			*p = ++idx;
		}
	}
	~ChunkAllocator()
	{
		free(chunk_ptr);
	}
	ChunkAllocator(const ChunkAllocator& other) = delete;
	ChunkAllocator(ChunkAllocator&& other) = delete;
	ChunkAllocator& operator=(const ChunkAllocator& other) = delete;
	ChunkAllocator& operator=(ChunkAllocator&& other)
	{
		memcpy(&chunk_ptr[0], &(other.chunk_ptr[0]), BlockSize * Blocks);
		free_blk_pos = other.free_blk_pos;
		free_blocks = other.free_blocks;
		return *this;
	}

	void* allocate(size_t size)
	{
		if ( (&chunk_ptr[0] + free_blk_pos) < (&chunk_ptr[0] + BlockSize * Blocks))
		{
			uint8_t* blk_ptr = &chunk_ptr[0] + free_blk_pos;
			free_blk_pos = *blk_ptr;
			--free_blocks;
			return blk_ptr;
		}
		return nullptr;
	}

	bool owns(void* mem_ptr)
	{
		return mem_ptr >= &chunk_ptr[0] && mem_ptr < (&chunk_ptr[0] + BlockSize * Blocks);
	}

	bool is_empty()
	{
		return free_blocks == Blocks;
	}
	
	void deallocate(void* mem_ptr, size_t size)
	{
		if (owns(mem_ptr))
		{
			*((uint8_t*)mem_ptr) = free_blk_pos;
			free_blk_pos = (((uint8_t*)mem_ptr) - &chunk_ptr[0]);
			++free_blocks;
		}
	}
private:
	uint8_t* chunk_ptr = nullptr;
	uint8_t free_blk_pos = 0;
	uint8_t free_blocks = Blocks;
};
