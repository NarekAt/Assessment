/////////////////// Description /////////////////////////
// An acquire fence prevents the memory reordering of
// any read which precedes it in program order with
// any read or write which follows it in program order.

// A release fence prevents the memory reordering of
// any read or write which precedes it in program
// order with any write which follows it in program order.

#pragma once

#include "LockingStrategy.h"
#include <atomic>

namespace Parallel
{

class AtomicFenseBasedLocking : public LockingStrategy
{
public:
    virtual void acquire() override
    {
        while (flag_.test_and_set(std::memory_order_relaxed));
        atomic_thread_fence(std::memory_order_acquire);
    }

    virtual void release() override
    {
        atomic_thread_fence(std::memory_order_release);
        flag_.clear(std::memory_order_relaxed);
    }

private:
    std::atomic_flag flag_ = ATOMIC_FLAG_INIT;
};

}
