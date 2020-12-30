#include "pch.h"

#include "../MM_LIB/mm_lib.h"

TEST(MemoryLeak, SimpleAllocationDeallocation) {
	const auto initial_mem = mm_stats::GetAllocatedMemory();
	char* c_ptr = new char();
	ASSERT_EQ(mm_stats::GetAllocatedMemory(), initial_mem + 1);
	delete c_ptr;
	ASSERT_EQ(mm_stats::GetAllocatedMemory(), initial_mem);
}

TEST(MemoryLeak, ArrayAllocationDeallocation) {
	const auto initial_mem = mm_stats::GetAllocatedMemory();
	char* c_ptr = new char[10];
	ASSERT_EQ(mm_stats::GetAllocatedMemory(), initial_mem + 10);
	delete[] c_ptr;
	ASSERT_EQ(mm_stats::GetAllocatedMemory(), initial_mem);
}