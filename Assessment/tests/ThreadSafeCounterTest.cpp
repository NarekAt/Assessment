#include "ThreadSafeCounter.h"
#include "MutexBasedLocking.h"
#include "AtomicSpinLock.h"
#include "AtomicFenseBasedLocking.h"
#include "TestUtils.h"

#include <functional>

#include <thread>

#include <gtest/gtest.h>

using s = std::chrono::seconds;
using namespace Parallel;

namespace
{

void runIncrement(ThreadSafeCounter& c)
{
    for (unsigned int i = 0; i != 100000000; ++i)
    {
        c.increment();
    }
}

auto run(ThreadSafeCounter& c)
{
    std::vector<std::thread> threads;

    Timer timer;
    timer.start();
    for (int i = 0; i != 8; ++i)
    {
        threads.push_back(std::thread(runIncrement,
            std::ref(c)));
    }

    for (auto& t : threads)
    {
        t.join();
    }
    timer.end();

    return timer.elapsedTime<s>();
}

}

TEST(ParallelTests, MutexBasedThreadSafeCounterBenchmark)
{
    auto l = std::make_unique<MutexBasedLocking<>>();
    ThreadSafeCounter c(l.get());

    const auto time = run(c);

    std::cout << "Elapsed time (in seconds) for mutex based locking " << time << std::endl;
    EXPECT_EQ(c.get(), 800000000);
}

TEST(ParallelTetst, RecursiveMutexBasedThreadSafeCounterBenchmark)
{
    auto l = std::make_unique<MutexBasedLocking<std::recursive_mutex>>();
    ThreadSafeCounter c(l.get());

    const auto time = run(c);
    std::cout << "Elapsed time (in seconds) for recursive mutex based locking " << time << std::endl;
    EXPECT_EQ(c.get(), 800000000);
}

TEST(ParallelTests, SpinLockThreadSafeCounterBenchmark)
{
    auto l = std::make_unique<AtomicSpinLock>();
    ThreadSafeCounter c(l.get());

    const auto time = run(c);
    std::cout << "Elapsed time (in seconds) for SpinLock based locking " << time << std::endl;
    EXPECT_EQ(c.get(), 800000000);
}

TEST(ParallelTests, TimedSpinLockThreadSafeCounterBenchmark)
{
    auto l = std::make_unique<TimedAtomicSpinLock>(std::chrono::milliseconds(1));
    ThreadSafeCounter c(l.get());

    const auto time = run(c);
    std::cout << "Elapsed time (in seconds) for TimedSpinLock based locking " << time << std::endl;
    EXPECT_EQ(c.get(), 800000000);
}

TEST(ParallelTests, AtomicFenceThreadSafeCounterBenchmark)
{
    auto l = std::make_unique<AtomicFenseBasedLocking>();
    ThreadSafeCounter c(l.get());

    const auto time = run(c);
    std::cout << "Elapsed time (in seconds) for AtomicFence based locking " << time << std::endl;
    EXPECT_EQ(c.get(), 800000000);
}