#pragma once

#include <cassert>
#include <memory>

template <size_t MaxSize, size_t Alignment = 16>
class StackAllocator
{
	alignas(Alignment) char m_stack[MaxSize];
	char* m_stack_ptr;
public:
	StackAllocator() : m_stack_ptr(m_stack) {}

	void* allocate(size_t size)
	{
		auto n_aligned_size = round_to_alignment(size);

		if ((m_stack_ptr + n_aligned_size) > (m_stack + MaxSize))
			return nullptr;
		
		void* result_addr = m_stack_ptr;
		m_stack_ptr += n_aligned_size;
		return result_addr;
	}

	void deallocate(void* mem_ptr, size_t size = 0)
	{
		auto temp_aligned_size = round_to_alignment(size);
		if (mem_ptr == (m_stack_ptr - temp_aligned_size))
		{
			m_stack_ptr -= temp_aligned_size;
			check_deallocation_requests();
		}
		else if( mem_ptr >= m_stack_ptr)
		{
			return;	// Invalid ptr to not allocated memory
		}
		else
		{
			add_deallocation_request(mem_ptr, temp_aligned_size);
			//assert(false);
		}
		return;
	}

	bool owns(void* mem_ptr)
	{
		return  mem_ptr >= m_stack && mem_ptr < (m_stack + MaxSize);
	}
private:
	size_t round_to_alignment(size_t val)
	{
		if(val > 0)
		{
			return Alignment * (1 + ((val-1) / Alignment));
		}
		return 0;
	}

	struct dealloc_rq
	{
		size_t size = 0;
		char* addr = nullptr;
	};
	
	void add_deallocation_request(void* mem_ptr, size_t size)
	{
		if(m_dealloc_stack == nullptr)
		{
			m_dealloc_stack = (char*) malloc(sizeof(dealloc_rq));
			dealloc_rq* dr = (dealloc_rq*)m_dealloc_stack;
			dr->size = size;
			dr->addr = (char*)mem_ptr;
		}
		else
		{
			m_dealloc_stack = (char*)realloc(m_dealloc_stack, sizeof(dealloc_rq) * (m_realloc_requests + 1));
			dealloc_rq* dr = (dealloc_rq*)(m_dealloc_stack + sizeof(dealloc_rq) * (m_realloc_requests));
			dr->size = size;
			dr->addr = (char*)mem_ptr;
		}

		m_realloc_requests++;
		// Keep it sorted
		size_t rr_i = m_realloc_requests-1;
		while (rr_i > 0) 
		{
			dealloc_rq* dr_i = (dealloc_rq*)(m_dealloc_stack + sizeof(dealloc_rq) * (rr_i));
			dealloc_rq* prev_dr_i = (dealloc_rq*)(m_dealloc_stack + sizeof(dealloc_rq) * (rr_i-1));
			if(dr_i->addr > prev_dr_i->addr)
			{
				break;
			}
			std::swap(dr_i->size, prev_dr_i->size);
			std::swap(dr_i->addr, prev_dr_i->addr);
			--rr_i;
		}	
	}
	
	void check_deallocation_requests()
	{
		while(m_realloc_requests > 0 && m_stack_ptr <= (peek_d_requests().addr + peek_d_requests().size))
		{
			if(m_stack_ptr == (peek_d_requests().addr + peek_d_requests().size))
			{
				m_stack_ptr -= peek_d_requests().size;
			}
			// Otherwise just ignore the request might be already been processed...
			pop_d_request();
		}
	}
	
	dealloc_rq& peek_d_requests()
	{
		return *  (dealloc_rq*)(m_dealloc_stack + sizeof(dealloc_rq) * (m_realloc_requests - 1));
	}

	void pop_d_request()
	{
		--m_realloc_requests;
		m_dealloc_stack = (char*)realloc(m_dealloc_stack, sizeof(dealloc_rq) * (m_realloc_requests));
	}
	
	size_t m_realloc_requests = 0;
	char* m_dealloc_stack = nullptr;
};