#pragma once

#include "fastapprox/fastlog.h"

#define log2 fasterlog2

namespace Opus
{
    template<typename T>
    inline T min(T a, T b)
    {
        return (a < b) ? a : b;
    }

    template<typename T>
    inline T max(T a, T b)
    {
        return (a > b) ? a : b;
    }

    template<typename T>
    inline T clamp(T d, T min, T max)
    {
        const T t = d < min ? min : d;
        return t > max ? max : t;
    }

    template<typename T>
    inline int sine(T x)
    {
        int a = -2 * (x < 0) + 1;
        return a * (x != 0);
    }

    template<typename T>
    inline T abs(T x)
    {
        return sine(x) * x;
    }

    inline int floor(float x) { return (int) x - (x < 0); }

    inline int ceil(float x) { return (int) x + (x > 0); }

    inline int round(float x) { return ceil(x - 0.5f); }

    inline int ilog2(int x) { return (floor(log2(x)) + 1) * (x > 0); }

}    // namespace Opus