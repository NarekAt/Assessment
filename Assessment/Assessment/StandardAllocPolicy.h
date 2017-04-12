#pragma once

#include "AllocatorTraits.h"
#include <limits>
#include <memory>

namespace MemMgmt
{

template<typename T>
class StandardAllocPolicy
{
public:
    ALLOCATOR_TRAITS(T)

public:
    template<typename U>
    struct rebind
    {
        typedef StandardAllocPolicy<U> other;
    };

public:
    StandardAllocPolicy() = default;
    ~StandardAllocPolicy() = default;

    StandardAllocPolicy(StandardAllocPolicy const&) = default;

    template <typename U>
    StandardAllocPolicy(StandardAllocPolicy<U> const&) {}

    pointer allocate(size_type cnt,
                     typename std::allocator<void>::const_pointer = 0)
    {
        return reinterpret_cast<pointer>(::operator new(cnt * sizeof(T)));
    }

    void deallocate(pointer p, size_type)
    {
        ::operator delete(p);
    }

    auto max_size() const
    {
        return std::numeric_limits<size_type>::max();
    }
};

template<typename T, typename T2>
inline bool operator==(StandardAllocPolicy<T> const&,
    StandardAllocPolicy<T2> const&)
{
    return true;
}

template<typename T, typename OtherAllocator>
inline bool operator==(StandardAllocPolicy<T> const&,
    OtherAllocator const&)
{
    return false;
}

}