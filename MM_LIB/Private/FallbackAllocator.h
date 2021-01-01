#pragma once

template <class Primary, class Fallback>
class FallbackAllocator : private Primary, private Fallback
{
public:
	void* allocate(size_t size)
	{
		void* mem_ptr = Primary::allocate(size);
		if(mem_ptr == nullptr)
		{
			mem_ptr = Fallback::allocate(size);
		}
		return mem_ptr;
	}
	
	void deallocate(void* mem_ptr, size_t size)
	{
		if (Primary::owns(mem_ptr))
			Primary::deallocate(mem_ptr, size);
		else if(Fallback::owns(mem_ptr))
			Fallback::deallocate(mem_ptr, size);
	}

	bool owns(void* mem_ptr)
	{
		return Primary::owns(mem_ptr) || Fallback::owns(mem_ptr);
	}
};