#pragma once

/* -------- TYPES -------- */
#include <cstdint>
namespace Silfur
{
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8 = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using f32 = float;
    using f64 = double;

    using b8 = bool;
}

#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

/* Ensure all types are of the correct size */
STATIC_ASSERT(sizeof(Silfur::u8) == 1, "Expected u8 to be 1 byte.");
STATIC_ASSERT(sizeof(Silfur::u16) == 2, "Expected u16 to be 2 bytes.");
STATIC_ASSERT(sizeof(Silfur::u32) == 4, "Expected u32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::u64) == 8, "Expected u64 to be 8 bytes.");

STATIC_ASSERT(sizeof(Silfur::i8) == 1, "Expected i8 to be 1 byte.");
STATIC_ASSERT(sizeof(Silfur::i16) == 2, "Expected i16 to be 2 bytes.");
STATIC_ASSERT(sizeof(Silfur::i32) == 4, "Expected i32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::i64) == 8, "Expected i64 to be 8 bytes.");

STATIC_ASSERT(sizeof(Silfur::f32) == 4, "Expected f32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::f64) == 8, "Expected f64 to be 8 bytes.");

/* -------- PLATFORM DETECTION -------- */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #ifndef _WIN64
        #error "x86 Builds are not supported!"
    #endif
#else
    /* Unknown platform */
    #error "Unknown platform!"
#endif

/* -------- INLINE -------- */
#ifdef _MSC_VER
    #define FORCEINLINE __forceinline
    #define FORCENOINLINE __declspec(noinline)
#elif defined(__clang__) || defined(__gcc__)
    #define FORCEINLINE inline __attribute__((always_inline))
    #define FORCENOINLINE __attribute__ ((noinline))
#else
    #define FORCEINLINE inline
    #define FORCENOINLINE
#endif

/* -------- C API CALL -------- */
/* Uses the C calling convention */
#ifndef CAPICALL
    #if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__WINRT__)) && !defined(__GNUC__)
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
    // #TODO Work on references system
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

    struct Version
    {
        u32 Major = 1;
        u32 Minor = 0;
        u32 Patch = 0;
    };
}
