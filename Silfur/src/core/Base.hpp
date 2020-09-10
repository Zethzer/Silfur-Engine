#pragma once

#ifndef __SILFUR_CORE_CORE_HPP__
#define __SILFUR_CORE_CORE_HPP__

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
#ifdef SF_CONFIG_DEBUG
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

/* -------- C API CALL -------- */
/* Uses the C calling convention */
#ifndef CAPICALL
    #if (defined(__WIN32__) || defined(__WINRT__)) && !defined(__GNUC__)
        #define CAPICALL __cdecl
    #elif defined(__OS2__) || defined(__EMX__)
        #define CAPICALL _System
        # if defined (__GNUC__) && !defined(_System)
            #  define _System /* for old EMX/GCC compat.  */
        # endif
    #else
        #define CAPICALL
    #endif
#endif

/* -------- BIND FUNCTION -------- */
#define SF_BIND_FN(fn) [](auto&&... args) -> decltype(auto) \
{ return fn(std::forward<decltype(args)>(args)...); }

#define SF_BIND_MEMBER_FN(fn) [this](auto&&... args) -> decltype(auto) \
{ return this->fn(std::forward<decltype(args)>(args)...); }

#include <memory>
namespace Silfur
{
    // #TODO Define engine version in ini file
    struct Version
    {
        uint32_t major;
        uint32_t minor;
        uint32_t patch;
    };

    enum class TypeEvent : uint8_t
    {
        System = 0,
        Game
    };

    // #TODO Work on references system
    template<typename T>
    using UniqueRef = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr UniqueRef<T> CreateUniqueRef(Args&& ... args)
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

#endif // __SILFUR_CORE_CORE_H__
