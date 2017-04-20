/////////////////// Description //////////////////////
// If an atomic store in thread A is tagged
// memory_order_release and an atomic load in
// thread B from the same variable is tagged
// memory_order_acquire, all memory writes
// (non - atomic and relaxed atomic)
// that happened - before the atomic store from
// the point of view of thread A, become visible
// side - effects in thread B, that is, once the atomic
// load is completed, thread B is guaranteed
// to see everything thread A wrote to memory.

#pragma once

#include "LockingStrategy.h"
#include <atomic>
#include <chrono>

namespace Parallel
{

class AtomicSpinLock : public LockingStrategy
{
public:
    virtual void acquire() override
    {
        while (flag_.test_and_set(std::memory_order_acquire));
    }

    virtual void release() override
    {
        flag_.clear(std::memory_order_release);
    }

protected:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

class TimedAtomicSpinLock : public AtomicSpinLock
{
public:
    TimedAtomicSpinLock(const std::chrono::milliseconds time)
        : AtomicSpinLock()
        , time_(time)
    {}

    virtual void acquire() override
    {
        while (flag_.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::sleep_for(time_);
        }
    }

private:
    std::chrono::milliseconds time_;
};

}
