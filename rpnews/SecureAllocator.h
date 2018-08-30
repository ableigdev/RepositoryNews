#ifndef RPNEWS_SECUREALLOCATOR_H
#define RPNEWS_SECUREALLOCATOR_H

#include "SecureZeroMemoryFunction.h"
#include <memory>

namespace secure
{
    template <typename DataType>
    class SecureAllocator : public std::allocator<DataType>
    {
    public:
        template <typename AnotherDataType> struct rebind { typedef SecureAllocator<AnotherDataType> other; };
        SecureAllocator() throw() {}
        SecureAllocator(const SecureAllocator&) throw() {}
        template <typename AnotherDataType> SecureAllocator(const SecureAllocator<AnotherDataType>&) throw() {}

        void deallocate(DataType* p, size_t counter)
        {
            secureZeroMemoryFunction((void*)p, counter);
            std::allocator<DataType>::deallocate(p, counter);
        }
    };
}

#endif //RPNEWS_SECUREALLOCATOR_H
