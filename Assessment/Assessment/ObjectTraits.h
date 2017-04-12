#pragma once

namespace MemMgmt
{

template<typename T>
class object_traits
{
public:

    typedef T type;

    template<typename U>
    struct rebind
    {
        typedef object_traits<U> other;
    };

    object_traits() = default;

    template<typename U>
    object_traits(object_traits<U> const& other) {}

    // Address of object
    type*       address(type&       obj) const { return &obj; }
    type const* address(type const& obj) const { return &obj; }

    void construct(type* ptr, type const& ref) const
    {
        new(ptr) type(ref);
    }

    void destroy(type* ptr) const
    {
        ptr->~type();
    }
};

};