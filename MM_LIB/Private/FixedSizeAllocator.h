#pragma once
#include <memory>

template<class Allocator, size_t s> 
class FixedSizeAllocator
{
	struct AllocatorNode
	{
		Allocator allocator;
		AllocatorNode* next = nullptr;
	} m_root;
	
	AllocatorNode* append_new_allocator()
	{
		AllocatorNode* it_a = &m_root;
		while (it_a->next != nullptr)
			it_a = it_a->next;

		void* node_addr = malloc(sizeof(AllocatorNode));
		it_a->next = new(node_addr) AllocatorNode;
		return it_a->next;
	}
public:
	void* allocate(size_t size)
	{
		if (size == s)
		{
			void* mem_ptr;
			// Find an available allocator that can handle the allocation request
			for (AllocatorNode* it_a = &m_root; it_a != nullptr; it_a = it_a->next)
			{
				mem_ptr = it_a->allocator.allocate(size);
				if(mem_ptr != nullptr)
				{
					return mem_ptr;
				}
			}
			// No allocator can accept the allocation request. Add a new allocator
			AllocatorNode* lastAllocator = append_new_allocator();
			return lastAllocator->allocator.allocate(size);
		}
		// Size request mismatch
		return nullptr;
	}

	void deallocate(void* mem_ptr, size_t size)
	{
		for (AllocatorNode* it_a = &m_root; it_a != nullptr; it_a = it_a->next)
		{
			if (it_a->allocator.owns(mem_ptr))
			{
				it_a->allocator.deallocate(mem_ptr, size);
				// @todo: Gestisci la rimozione del nodo in caso...
				return;
			}
		}
	}

	void owns(void* mem_ptr, size_t size)
	{
		for (AllocatorNode* it_a = &m_root; it_a != nullptr; it_a = it_a->next)
		{
			if (it_a->allocator.owns(mem_ptr))
			{				
				return true;
			}
		}
		return false;
	}
};
