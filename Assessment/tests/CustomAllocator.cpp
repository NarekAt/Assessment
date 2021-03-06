#include "Allocator.h"
#include "DebugAllocPolicy.h"
#include <gtest/gtest.h>

using namespace MemMgmt;

TEST(MemoryManagement, DebugAllocTest)
{
    std::vector<int, Allocator<int, DebugAllocPolicy<int>>> v;

    for (int i = 0; i != 100; ++i)
    {
        v.push_back(i);
    }

    std::cout << "Without reserved capacity" << std::endl;
    std::cout << "Capacity = " << v.capacity() << std::endl;
    std::cout << "Total Allocations = " << v.get_allocator().totalAllocations() << std::endl;
    std::cout << "Peak Allocations = " << v.get_allocator().peakAllocations() << std::endl;

    EXPECT_EQ(v.capacity(), v.get_allocator().currentAllocations());

    v.clear();

    std::vector<int, Allocator<int, DebugAllocPolicy<int>>> v2;
    v2.reserve(100);

    for (int i = 0; i != 100; ++i)
    {
        v.push_back(i);
    }
    std::cout << "With reserved capacity" << std::endl;
    std::cout << "Capacity = " << v2.capacity() << std::endl;
    std::cout << "Total Allocations = " << v2.get_allocator().totalAllocations() << std::endl;
    std::cout << "Peak Allocations = " << v2.get_allocator().peakAllocations() << std::endl;

    EXPECT_EQ(v.capacity(), v.get_allocator().currentAllocations());
}