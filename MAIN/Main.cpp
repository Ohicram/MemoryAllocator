#include "../MM_LIB/mm_lib.h"

#include <iostream>

int main()
{
	const size_t N = 100;
	char* c_arr[N];

	for(size_t i = 0; i < N; ++i)
	{
		c_arr[i] = new char();
	}

	for (size_t i = 20; i < 40; ++i)
	{
		delete c_arr[i];
	}

	//delete c_ptr;

	//std::cout << "Dieser zug endet hier......" << std::endl;
	return 0;
}

