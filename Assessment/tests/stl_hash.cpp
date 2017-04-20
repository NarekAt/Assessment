#include <unordered_set>
#include <typeinfo>

#include <gtest/gtest.h>

std::unordered_set<int> intset = { 1,2,3,5,7,11,13,17,19 };

template<class  T>
void checkIteratorCategory(const T& cont)
{
    if (typeid(typename std::iterator_traits<typename T::iterator>::iterator_category)
        == typeid(std::bidirectional_iterator_tag))
    {
        std::cout << "chaining style: doubly-linked" << "\n";
    }
    else
    {
        std::cout << "chaining style: singly-linked" << "\n";
    }
    std::cout << std::endl;
}

template <class T>
void printData(const T& cont)
{
    std::cout << "data: " << "\n";
    for (auto idx = 0; idx != cont.bucket_count(); ++idx)
    {
        std::cout << " b[" << std::setw(2) << idx << "]: ";
        for (auto pos = cont.begin(idx); pos != cont.end(idx); ++pos)
        {
            std::cout << *pos << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

TEST(STL_TESTS, HashBucketInterfaceTest)
{
    EXPECT_EQ(intset.size(), 9);
    EXPECT_EQ(intset.bucket_count(), 64);
    EXPECT_EQ(intset.load_factor(), 0.140625);
    EXPECT_EQ(intset.max_load_factor(), 1);

    checkIteratorCategory(intset);

    printData(intset);
}

TEST(STL_TESTS, HashBucketInterfaceTest2)
{
    intset.insert({ -7,18,33,4 });

    EXPECT_EQ(intset.size(), 13);
    EXPECT_EQ(intset.bucket_count(), 64);
    EXPECT_EQ(intset.load_factor(), 0.203125);
    EXPECT_EQ(intset.max_load_factor(), 1);

    checkIteratorCategory(intset);

    printData(intset);
}