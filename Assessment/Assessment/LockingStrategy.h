#pragma once

namespace Parallel
{

class LockingStrategy
{
public:
    virtual void acquire() = 0;
    virtual void release() = 0;
    virtual ~LockingStrategy() = default;
};

}
