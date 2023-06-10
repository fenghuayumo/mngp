#pragma once
#include "core/base_type.h"
#include <memory>
class  PlatformBase
{
    
public:
    inline static void MemoryCopy(void* dst, const void* src, uint64 size)
    {
        memcpy(dst, src, static_cast<size_t>(size));
    }

    inline static void MemorySet(void* dst, uint64 size, int32 value)
    {
        memset(dst, value, static_cast<size_t>(size));
    }

    inline static void MemoryClear(void* dst, uint64 size)
    {
        memset(dst, 0, static_cast<size_t>(size));
    }
};

#define Platform PlatformBase