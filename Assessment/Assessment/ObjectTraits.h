#pragma once

namespace MemMgmt
{

template<typename T>
class ObjectTraits
{
public:

    typedef T type;

    template<typename U>
    struct rebind
    {
        typedef ObjectTraits<U> other;
    };

    ObjectTraits() = default;

    template<typename U>
    ObjectTraits(ObjectTraits<U> const& other) {}

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