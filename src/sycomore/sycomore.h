#ifndef _a5b5eb59_d6dc_4067_b736_f03a01085d12
#define _a5b5eb59_d6dc_4067_b736_f03a01085d12

#include <complex>
#include <vector>

namespace sycomore
{

using Real = double;
using Complex = std::complex<Real>;

Real rad2deg(Real const value);
Real deg2rad(Real const value);

using Index = std::vector<int>;
using Shape = std::vector<unsigned int>;
using Stride = std::vector<unsigned int>;

}

#endif // _a5b5eb59_d6dc_4067_b736_f03a01085d12