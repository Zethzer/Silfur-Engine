#pragma once

#ifndef CORE_H
#define CORE_H

/* -------- PLATFORM DETECTION -------- */
#ifdef _WIN32
    /* Windows x64/x86 */
    #ifndef _WIN64
        #error "x86 Builds are not supported!"
    #endif
#else
    /* Unknown compiler/platform */
    #error "Unknown platform!"
#endif

/* -------- ASSERTS -------- */
#include "debug-trap.h"
#ifdef SF_DEBUG
    #define SF_ENABLE_ASSERTS
#endif

#ifdef SF_ENABLE_ASSERTS
#ifdef SF_CORE
    #define SF_CORE_ASSERT(x, ...) { if(!(x)) { SF_CORE_ERROR(Assert, "Assertion Failed: {}", __VA_ARGS__); psnip_trap(); } }
#else
    #define SF_ASSERT(x, ...) { if(!(x)) { SF_ERROR(Assert, "Assertion Failed: {}", __VA_ARGS__); psnip_trap(); } }
#endif
#else
    #define SF_ASSERT(x, ...)
    #define SF_CORE_ASSERT(x, ...)
#endif

/* -------- INLINE -------- */
#ifdef _MSC_VER
    #define FORCEINLINE __forceinline
    #define FORCENOINLINE __declspec(noinline)
#elif __GNUC__
    #define FORCEINLINE inline __attribute__((always_inline))
    #define FORCENOINLINE __attribute__ ((noinline))
#else
    #define FORCEINLINE inline
    #define FORCENOINLINE
#endif

#include <memory>
namespace Silfur
{
    // TODO (Zeth) : Work on references system
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif // CORE_H
