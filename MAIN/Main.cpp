#include "../MM_LIB/mm_lib.h"

#include <iostream>

int main()
{
	const auto initial_mem = mm_stats::GetAllocatedMemory();
	for(int i  = 0; i < 20; ++i)
	{
		char* c_ptr = new char();
	}
	//delete c_ptr;

	//std::cout << "Dieser zug endet hier......" << std::endl;
	return 0;
}

