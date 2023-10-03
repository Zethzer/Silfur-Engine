#pragma once

/* -------- TYPES -------- */
#include <cstdint>
namespace Silfur
{
    using uint8 = uint8_t;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    using int8 = int8_t;
    using int16 = int16_t;
    using int32 = int32_t;
    using int64 = int64_t;

    using float32 = float;
    using float64 = double;
}

#if defined(__clang__) || defined(__gcc__)
    #define STATIC_ASSERT _Static_assert
#else
    #define STATIC_ASSERT static_assert
#endif

/* Ensure all types are of the correct size */
STATIC_ASSERT(sizeof(Silfur::uint8) == 1, "Expected uint8 to be 1 byte.");
STATIC_ASSERT(sizeof(Silfur::uint16) == 2, "Expected uint16 to be 2 bytes.");
STATIC_ASSERT(sizeof(Silfur::uint32) == 4, "Expected uint32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::uint64) == 8, "Expected uint64 to be 8 bytes.");

STATIC_ASSERT(sizeof(Silfur::int8) == 1, "Expected int8 to be 1 byte.");
STATIC_ASSERT(sizeof(Silfur::int16) == 2, "Expected int16 to be 2 bytes.");
STATIC_ASSERT(sizeof(Silfur::int32) == 4, "Expected int32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::int64) == 8, "Expected int64 to be 8 bytes.");

STATIC_ASSERT(sizeof(Silfur::float32) == 4, "Expected float32 to be 4 bytes.");
STATIC_ASSERT(sizeof(Silfur::float64) == 8, "Expected float64 to be 8 bytes.");

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
        uint32 Major = 1;
        uint32 Minor = 0;
        uint32 Patch = 0;
    };
}
