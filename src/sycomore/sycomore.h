#ifndef _a5b5eb59_d6dc_4067_b736_f03a01085d12
#define _a5b5eb59_d6dc_4067_b736_f03a01085d12

#include <complex>
#include <vector>

#include "sycomore/Array.h"
#include "sycomore/units.h"

namespace sycomore
{

using Real = double;
using Complex = std::complex<Real>;

using Index = Array<int>;
using Shape = Array<unsigned int>;
using Stride = Array<unsigned int>;

using Point = Array<units::Length>;

using Diffusion = units::div<units::pow<units::Length, 2>, units::Time>;

// NOTE: gradient moment is gamma * integral(g(t)*dt), with gamma in
// [T^-1 * s^-1] and g(t) in [T * m^-1] (thus integral(g(t)*dt)
// in [T * m^-1 * s]). Gradient moment is then in [m^-1]
using GradientMoment = units::pow<units::Length, -1>;

template<typename T>
std::vector<T> linspace(T min, T max, size_t size)
{
    std::vector<T> result(size, T(0));
    auto const delta = (max-min)/(size-1);
    for(size_t i=0; i<result.size(); ++i)
    {
        result[i] = min+i*delta;
    }
    return result;
}

template<typename T>
std::vector<T> linspace(T span, size_t size)
{
    return linspace(-span/2., span/2., size);
}

}

#endif // _a5b5eb59_d6dc_4067_b736_f03a01085d12
