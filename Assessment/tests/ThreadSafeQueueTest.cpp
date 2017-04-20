#include "ThreadSafeQueue_Impl.h"
#include <thread>
#include <functional>
#include <gtest/gtest.h>
#include <future>

namespace
{

typedef Parallel::ThreadSafeQueue<int> QueueT;

void joinThreads(std::vector<std::thread>& threads)
{
    for (auto& t : threads)
    {
        t.join();
    }
}

}

TEST(QueueWriteTest, ParallelTests)
{
    QueueT q;

    std::vector<std::thread> threads;

    for (int i = 0; i != 1000; ++i)
    {
        threads.push_back(std::thread(&QueueT::push, &q, i));
    }

    for (int i = 0; i != 20; ++i)
    {
        QueueT::value_type v;
        threads.push_back(std::thread(&QueueT::pop, &q, std::ref(v)));
    }

    joinThreads(threads);

    EXPECT_EQ(q.size(), 980);
}

TEST(ParallelTests, QueueReadWriteTest)
{
    QueueT q;

    std::vector<std::thread> threads;

    for (int i = 0; i != 1000; ++i)
    {
        threads.push_back(std::thread(&QueueT::push, &q, i));
    }

    for (int i = 0; i != 200; ++i)
    {
        threads.push_back(std::thread(&QueueT::size, &q));
    }

    joinThreads(threads);

    EXPECT_EQ(q.size(), 1000);
}