#ifndef RPNEWS_SECUREZEROMEMORYFUNCTION_H
#define RPNEWS_SECUREZEROMEMORYFUNCTION_H

namespace secure
{
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
}

#endif //RPNEWS_SECUREZEROMEMORYFUNCTION_H
