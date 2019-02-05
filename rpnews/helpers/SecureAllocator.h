#ifndef RPNEWS_SECUREALLOCATOR_H
#define RPNEWS_SECUREALLOCATOR_H

#include <memory>

namespace secure
{
    template <typename DataType>
    class SecureAllocator : public std::allocator<DataType>
    {
    public:
        template <typename AnotherDataType> struct rebind { typedef SecureAllocator<AnotherDataType> other; };
        SecureAllocator() noexcept {}
        SecureAllocator(const SecureAllocator&) noexcept {}
        template <typename AnotherDataType> SecureAllocator(const SecureAllocator<AnotherDataType>&) noexcept {}

        void deallocate(DataType* p, size_t counter)
        {
            secureZeroMemoryFunction(static_cast<void*>(p), counter);
            std::allocator<DataType>::deallocate(p, counter);
        }

    private:
        void* secureZeroMemoryFunction(void* ptr, unsigned long counter)
        {
            volatile char* vptr = static_cast<volatile char*>(ptr);
            while (counter)
            {
                *vptr = 0;
                ++vptr;
                --counter;
            }
            return ptr;
        }
    };
}

#endif //RPNEWS_SECUREALLOCATOR_H
