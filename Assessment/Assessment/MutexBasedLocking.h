#pragma once

#include "LockingStrategy.h"
#include <mutex>

namespace Parallel
{

template <typename MutexType = std::mutex>
class MutexBasedLocking : public LockingStrategy
{
public:
    MutexBasedLocking()
        : LockingStrategy()
        , owns_(false)
    {}

    virtual void acquire() override
    {
        mutex_.lock();
        owns_ = true;
    }

    virtual void release() override
    {
        mutex_.unlock();
        owns_ = false;
    }

    virtual ~MutexBasedLocking()
    {
        if (owns_)
            mutex_.unlock();
    }

private:
    MutexType  mutex_;
    bool       owns_;
};

}
