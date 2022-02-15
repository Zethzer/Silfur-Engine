#ifdef SF_DEBUG
    #define SF_ENABLE_ASSERTS
#endif

#ifdef SF_ENABLE_ASSERTS
    #include <debug-trap.h>
    #define debugBreak()

    #define SF_ASSERT(expr)                                                                     \
    {                                                                                           \
        if (!(expr)) {                                                                          \
            printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__);  \
            psnip_trap();                                                                       \
        }                                                                                       \
    }

    #define SF_ASSERT_MSG(expr, message)                                                        \
    {                                                                                           \
        if (!(expr)) {                                                                          \
            printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__);  \
            psnip_trap();                                                                       \
        }                                                                                       \
    }

    #ifdef SF_DEBUG
        #define SF_ASSERT_DEBUG(expr)                                                              \
        {                                                                                          \
            if (!(expr)) {                                                                            \
                printf("Assertion Failed: {%s} in file %s on line %s", #expr, __FILE__, __LINE__); \
                psnip_trap();                                                                      \
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