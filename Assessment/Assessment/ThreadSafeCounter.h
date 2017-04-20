#pragma once

#include "LockingStrategy.h"

namespace Parallel
{

class ThreadSafeCounter
{
public:
    ThreadSafeCounter(LockingStrategy* l)
        : value_(0u)
        , lock_(l)
    {}

    void increment()
    {
        lock_->acquire();

        ++value_;

        lock_->release();
    }

    auto get()
    {
        return value_;
    }

private:
    unsigned int value_;
    LockingStrategy* lock_;
};

}