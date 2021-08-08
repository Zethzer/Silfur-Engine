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

/* -------- EXPORT -------- */
#ifdef SF_EXPORT
    #ifdef _MSC_VER
        #define SF_API __declspec(dllexport)
    #else
        #define SF_API __attribute__((visibility("default")))
    #endif
#else
    #ifdef _MSC_VER
        #define SF_API __declspec(dllimport)
    #else
        #define SF_API
    #endif
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