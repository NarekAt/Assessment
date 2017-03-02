#include <vector>
#include <algorithm>

#include <gtest/gtest.h>

TEST(IsSorted, STL_TEST)
{
	std::vector<int> coll = { 1,2,3,3,5,78,99,102,333 };

	EXPECT_TRUE(std::is_sorted(coll.begin(), coll.end()));

	std::vector<int> coll2 = { 1, 4, 9, 19, 77, 66, 78, 90 };

	auto firstUnsorted = std::is_sorted_until(coll2.begin(), coll2.end());

	EXPECT_EQ(*firstUnsorted, 66);
}

TEST(PartitionCheck, STL_TEST)
{
	std::vector<int> coll = { 5, 3, 9, 1, 3, 4, 8, 2, 6 };

	auto isOdd = [](int elem)
	{
		return elem % 2 == 1;
	};

	EXPECT_TRUE(is_partitioned(coll.cbegin(), coll.cend(), isOdd));

	auto pos = partition_point(coll.cbegin(), coll.cend(), isOdd);

	EXPECT_EQ(*pos, 4);
}

TEST(ContainerHeapCheck, STL_TEST)
{
	std::vector<int> coll1 = { 9, 8, 7, 7, 7, 5, 4, 2, 1 };
	std::vector<int> coll2 = { 5, 3, 2, 1, 4, 7, 9, 8, 6 };

	EXPECT_TRUE(is_heap(coll1.cbegin(), coll1.cend()));
	EXPECT_FALSE(is_heap(coll2.cbegin(), coll2.cend()));
}

TEST(Permutations, STL_TEST)
{
	std::string s = "aba";

	std::vector<std::string> permutations = { "aab", "aba", "baa" };
	std::sort(s.begin(), s.end());


	while (std::next_permutation(s.begin(), s.end()))
	{
		EXPECT_TRUE(s == "aba" || s == "baa");
	}
}

TEST(HeapAlgorithms, STL_TEST)
{
	std::vector<int> coll = { 3, 4, 5, 6, 7, 5, 6, 7, 8, 9, 1, 2, 3, 4 };
	std::make_heap(coll.begin(), coll.end());

	std::vector<int> expected = { 9, 8, 6, 7, 7, 5, 5, 3, 6, 4 ,1, 2, 3, 4 };

	EXPECT_TRUE(std::equal(coll.begin(), coll.end(), expected.begin()));

	// pop next element out of the heap
	std::pop_heap(coll.begin(), coll.end());
	coll.pop_back();

	expected.clear();
	expected = { 8, 7, 6, 7, 4, 5, 5, 3, 6, 4, 1, 2, 3 };

	EXPECT_TRUE(std::equal(coll.begin(), coll.end(), expected.begin()));
}