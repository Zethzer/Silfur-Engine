#ifdef SF_DEBUG
    #define SF_ENABLE_ASSERTS
#endif

#ifdef SF_ENABLE_ASSERTS
    #include <cstdio>
    #ifdef _MSC_VER
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif
    
    #define SF_ASSERT(expr)                                                                     \
    {                                                                                           \
        if (!(expr)) {                                                                          \
            printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__);  \
            debugBreak();                                                                       \
        }                                                                                       \
    }

    #define SF_ASSERT_MSG(expr, message)                                                        \
    {                                                                                           \
        if (!(expr)) {                                                                          \
            printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__);  \
            debugBreak();                                                                       \
        }                                                                                       \
    }

    #ifdef SF_DEBUG
        #define SF_ASSERT_DEBUG(expr)                                                              \
        {                                                                                          \
            if (!(expr)) {                                                                            \
                printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__); \
                debugBreak();                                                                      \
            }                                                                                      \
        }
    #else
        #define SF_ASSERT_DEBUG(expr)
    #endif
#else
    #define SF_ASSERT(expr)
    #define SF_ASSERT_MSG(expr, message)
    #define SF_ASSERT_DEBUG(expr)
#endif