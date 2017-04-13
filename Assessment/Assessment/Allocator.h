#pragma once
#include "StandardAllocPolicy.h"
#include "ObjectTraits.h"

namespace MemMgmt
{

template<typename T,
         typename Policy = StandardAllocPolicy<T>,
         typename Traits = ObjectTraits<T>>
class Allocator : public Policy, public Traits
{
private:
    typedef Policy AllocationPolicy;
    typedef Traits TTraits;

public:
    FORWARD_ALLOCATOR_TRAITS(AllocationPolicy)

public:
    template<typename U>
    struct rebind
    {
        typedef Allocator<U,
            typename AllocationPolicy::template rebind<U>::other,
            typename TTraits::template rebind<U>::other
        > other;
    };

public:
    Allocator() = default;
    ~Allocator() = default;
    Allocator(Allocator const& rhs)
        : Traits(rhs)
        , Policy(rhs)
    {}

    template <typename U>
    Allocator(Allocator<U> const&) = default;

    template <typename U, typename P, typename T2>
    Allocator(Allocator<U, P, T2> const& rhs)
        : Traits(rhs)
        , Policy(rhs)
    {}
};

template<typename T, typename P, typename Tr>
inline bool operator==(Allocator<T, P, Tr> const& lhs,
                       Allocator<T, P, Tr> const& rhs)
{
    return operator==(static_cast<P&>(lhs), static_cast<P&>(rhs));
}

template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
    inline bool operator==(Allocator<T, P, Tr> const& lhs,
                           Allocator<T2, P2, Tr2> const& rhs)
{
    return operator==(static_cast<P&>(lhs), static_cast<P2&>(rhs));
}

template<typename T, typename P, typename Tr, typename OtherAllocator>
inline bool operator==(Allocator<T, P, Tr> const& lhs,
                       OtherAllocator const& rhs)
{
    return operator==(static_cast<P&>(lhs), rhs);
}

template<typename T, typename P, typename Tr>
inline bool operator!=(Allocator<T, P, Tr> const& lhs,
                       Allocator<T, P, Tr> const& rhs)
{
    return !operator==(lhs, rhs);
}

template<typename T, typename P, typename Tr, typename T2, typename P2, typename Tr2>
inline bool operator!=(Allocator<T, P, Tr> const& lhs,
                       Allocator<T2, P2, Tr2> const& rhs)
{
    return !operator==(lhs, rhs);
}

template<typename T, typename P, typename Tr, typename OtherAllocator>
inline bool operator!=(Allocator<T, P, Tr> const& lhs,
                       OtherAllocator const& rhs)
{
    return !operator==(lhs, rhs);
}

}