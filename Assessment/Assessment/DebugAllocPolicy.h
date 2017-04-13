#pragma once

#include "StandardAllocPolicy.h"

namespace MemMgmt
{

template<typename T, typename Policy = StandardAllocPolicy<T>>
class DebugAllocPolicy : public Policy
{
private:
    typedef Policy AllocationPolicy;

public:
    template<typename U>
    struct rebind
    {
        typedef DebugAllocPolicy<U,
            typename AllocationPolicy::template rebind<U>::other
            > other;
    };

public:
    DebugAllocPolicy()
        : total_(0)
        , current_(0)
        , peak_(0)
    {}

    DebugAllocPolicy(DebugAllocPolicy const& rhs)
        : Policy(rhs)
        , total_(rhs.total_)
        , current_(rhs.current_)
        , peak_(rhs.peak_)
    {}

    template <typename U>
    DebugAllocPolicy(DebugAllocPolicy<U> const& rhs)
        : Policy(rhs)
        , total_(0)
        , current_(0)
        , peak_(0)
    {}

    auto
    allocate(typename AllocationPolicy::size_type cnt,
             typename std::allocator<void>::const_pointer hint = 0)
    {
        auto p = AllocationPolicy::allocate(cnt, hint);
        this->total_ += cnt;
        this->current_ += cnt;
        if (this->current_ > this->peak_)
        {
            this->peak_ = this->current_;
        }
        return p;
    }

    void
    deallocate(typename AllocationPolicy::pointer p,
               typename AllocationPolicy::size_type cnt)
    {
        AllocationPolicy::deallocate(p, cnt);
        this->current_ -= cnt;
    }

    auto TotalAllocations()
    { return this->total_; }

    auto CurrentAllocations()
    { return this->current_; }

    auto PeakAllocations()
    { return this->peak_; }

private:
    typename AllocationPolicy::size_type total_;
    typename AllocationPolicy::size_type current_;
    typename AllocationPolicy::size_type peak_;
};

template<typename T, typename Policy, typename T2, typename Policy2>
inline bool operator==(DebugAllocPolicy<T, Policy> const& lhs,
                       DebugAllocPolicy<T2, Policy2> const& rhs)
{
    return operator==(static_cast<Policy&>(lhs), static_cast<Policy&>(rhs));
}

template<typename T, typename Policy, typename OtherAllocator>
inline bool operator==(DebugAllocPolicy<T, Policy> const& lhs,
                       OtherAllocator const& rhs)
{
    return operator==(static_cast<Policy&>(lhs), rhs);
}

}