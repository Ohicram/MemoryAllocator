#include "../MM_LIB/mm_lib.h"

#include <iostream>

template<size_t S>
struct CustomSize
{
	char junk[S];
};

int main()
{
	const size_t N = 100;
	char* c_arr[N];

	CustomSize<16>* smallObj;
	CustomSize<32>* largeObj;
	smallObj = new CustomSize<16>();
	largeObj = new CustomSize<32>();
/*	for (size_t i = 0; i < 10; ++i)
	{
		c_arr[i] = new char();
		*(c_arr[i]) = '0' + (i);
	}

	delete c_arr[2];
	delete c_arr[7];
	delete c_arr[5];
	for (int i = 9; i >= 0; --i)
	{
		delete c_arr[i];
	}*/


	/*for(size_t i = 0; i < N; ++i)
	{
		c_arr[i] = new char();
		*(c_arr[i]) = '0' + (i/10);
	}
	std::cout << "c_arr[19]: " << *(c_arr[19]) << std::endl;
	std::cout << "c_arr[29]: " << *(c_arr[29]) << std::endl;
	std::cout << "c_arr[39]: " << *(c_arr[39]) << std::endl;
	std::cout << "c_arr[49]: " << *(c_arr[49]) << std::endl;
	std::cout << "c_arr[99]: " << *(c_arr[99]) << std::endl;
	for (size_t i = 20; i < 40; ++i)
	{
		delete c_arr[i];
	}
	std::cout << "c_arr[19]: " << *(c_arr[19]) << std::endl;
	std::cout << "c_arr[29]: " << *(c_arr[29]) << std::endl;
	std::cout << "c_arr[39]: " << *(c_arr[39]) << std::endl;
	std::cout << "c_arr[49]: " << *(c_arr[49]) << std::endl;
	std::cout << "c_arr[99]: " << *(c_arr[99]) << std::endl;
	for (size_t i = 20; i < 40; ++i)
	{
		c_arr[i] = new char();
		*(c_arr[i]) = '0' + (i / 10);
	}
	std::cout << "c_arr[19]: " << *(c_arr[19]) << std::endl;
	std::cout << "c_arr[29]: " << *(c_arr[29]) << std::endl;
	std::cout << "c_arr[39]: " << *(c_arr[39]) << std::endl;
	std::cout << "c_arr[49]: " << *(c_arr[49]) << std::endl;
	std::cout << "c_arr[99]: " << *(c_arr[99]) << std::endl;
	//std::cout << "Dieser zug endet hier......" << std::endl;*/
	return 0;
}
