

#ifndef CDSUTIL_UTIL_HPP
#define CDSUTIL_UTIL_HPP

#include <cassert>
#include <chrono>
#include <cstdint>
#include <stdarg.h>
#include <utility>

namespace CdsUtil
{
    // checks if the provided classes have an == operator between each other.
    // https://stackoverflow.com/a/35207812
    template <class T, class EqualTo>
    struct has_operator_equal_impl
    {
        template <class U, class V>
        static auto test(U*)
            -> decltype(std::declval<U>() == std::declval<V>());
        template <typename, typename>
        static auto test(...) -> std::false_type;

        using type =
            typename std::is_same<bool, decltype(test<T, EqualTo>(0))>::type;
    };

    template <class T, class EqualTo = T>
    struct has_operator_equal : has_operator_equal_impl<T, EqualTo>::type
    {
    };

    // generate a random number using xorshift32 using provided seed.
    uint32_t
    xorshift32(uint32_t seed)
    {
        seed ^= seed >> 13;
        seed ^= seed << 17;
        seed ^= seed >> 5;
        return seed;
    }

    uint32_t
    rand_nano()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto dur = now.time_since_epoch();
        auto nano = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
        return xorshift32(static_cast<uint32_t>(nano));
    }

    // generate a random nano-seeded num. constrained
    // to range [min, max].
    uint32_t
    rand_range(uint32_t min, uint32_t max)
    {
        // the modulo constrains to [0, range-size -1] and
        // adding min constrains to [min, max]
        return (rand_nano() % (max - min + 1)) + min;
    }

    // generates an ASCII string
    std::string
    string_generator()
    {
        std::string ret = "";
        for (size_t i = 0; i < 10; ++i)
            ret += ((char)rand_range(32, 126));
        return ret;
    }

    // asserts with a msg and with printf style formatting
    void
    assertf(int line, bool condition, const char* msg, ...)
    {
        // if condition is false
        if (!condition)
        {
            // begin print msg
            printf("LINE %d: Assertion failed! ", line);

            // variadic arguments: declare, init, print, cleanup.
            va_list args;
            va_start(args, msg);
            vprintf(msg, args);
            va_end(args);

            // obligatory newline & terminate.
            printf("\n");
            abort();
        }
    }
} // namespace CdsUtil

#endif // CDSUTIL_UTIL_HPP
