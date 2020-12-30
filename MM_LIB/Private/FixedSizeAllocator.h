#pragma once
#include <memory>

template<class Allocator, size_t s> 
class FixedSizeAllocator
{
	Allocator* batch = nullptr;
	size_t batch_size = 0;
public:
	void* allocate(size_t size)
	{
		if (size == s)
		{
			void* mem_ptr;
			// Find an available allocator that can handle the allocation request
			for (size_t i = 0; i < batch_size; ++i)
			{
				mem_ptr = batch[i].allocate(size);
				if(mem_ptr != nullptr)
				{
					return mem_ptr;
				}
			}
			// No allocator can accept the allocation request. Add a new allocator
			Allocator* lastAllocator = add_allocator();
			return lastAllocator->allocate(size);
		}
		// Size request mismatch
		return nullptr;
	}

	void deallocate(void* mem_ptr, size_t size)
	{
		for (size_t i = 0; i < batch_size; ++i)
		{
			if (batch[i].owns(mem_ptr))
			{
				batch[i].deallocate(mem_ptr, size);
				if (batch[i].is_empty())
					request_remove_allocator(i);
				return;
			}
		}
	}

	void owns(void* mem_ptr, size_t size)
	{
		for (size_t i = 0; i < batch_size; ++i)
		{
			if (batch[i].owns(mem_ptr))
			{
				return true;
			}
		}
		return false;
	}

private:
	void request_remove_allocator(size_t idx)
	{
		batch[idx] = std::move(batch[batch_size - 1]);

		if (batch_size == 1)
		{
			free(batch);
		}
		else
		{
			batch = (Allocator*)realloc((void*)batch, sizeof(Allocator) * (batch_size - 1));
		}
		batch_size -= 1;
	}

	Allocator* add_allocator()
	{
		batch_size += 1;
		if (batch == nullptr)
		{
			batch = (Allocator*)malloc(sizeof(Allocator));
			new(batch) Allocator();
		}
		else
		{
			batch = (Allocator*)realloc((void*)batch, sizeof(Allocator) * (batch_size));
			new(&batch[batch_size - 1]) Allocator();
		}
		return &batch[batch_size - 1];
	}
};
