#include "Allocator.h"
#include "DebugAllocPolicy.h"
#include <gtest/gtest.h>

using namespace MemMgmt;

TEST(DebugAllocTest, MemoryManagement)
{
    std::vector<int, Allocator<int, DebugAllocPolicy<int>>> v;

    for (int i = 0; i != 100; ++i)
    {
        v.push_back(i);
    }

    std::cout << "Without reserved capacity" << std::endl;
    std::cout << "Capacity = " << v.capacity() << std::endl;
    std::cout << "Total Allocations = " << v.get_allocator().TotalAllocations() << std::endl;
    std::cout << "Peak Allocations = " << v.get_allocator().PeakAllocations() << std::endl;

    EXPECT_EQ(v.capacity(), v.get_allocator().CurrentAllocations());

    v.clear();

    std::vector<int, Allocator<int, DebugAllocPolicy<int>>> v2;
    v2.reserve(100);

    for (int i = 0; i != 100; ++i)
    {
        v.push_back(i);
    }
    std::cout << "With reserved capacity" << std::endl;
    std::cout << "Capacity = " << v2.capacity() << std::endl;
    std::cout << "Total Allocations = " << v2.get_allocator().TotalAllocations() << std::endl;
    std::cout << "Peak Allocations = " << v2.get_allocator().PeakAllocations() << std::endl;

    EXPECT_EQ(v.capacity(), v.get_allocator().CurrentAllocations());
}