#ifndef _faa6a046_30f6_4e87_91a6_033e2330b405
#define _faa6a046_30f6_4e87_91a6_033e2330b405

#include <tuple>
#include <utility>
#include <vector>

#include "sycomore/Quantity.h"
#include "sycomore/Species.h"
#include "sycomore/sycomore.h"
#include "sycomore/sycomore_api.h"
#include "sycomore/units.h"

namespace sycomore
{

namespace epg
{

namespace operators
{

/// @brief Return the row-wise matrix corresponding to the EPG pulse operator.
SYCOMORE_API std::vector<Complex> pulse(Real angle, Real phase);

/**
 * @brief Return the scalars associated respectively with relaxation of 
 * the F̃ states and Z̃ states.
 */
SYCOMORE_API std::pair<Real, Real> relaxation(Real R1, Real R2, Real duration);

/**
 * @brief Return the scalars associated respectively with diffusion of 
 * respectively the F̃_k, F̃^*_{-k}, and Z̃_k states.
 */
SYCOMORE_API std::tuple<Real, Real, Real> diffusion(
    Real D, Real duration, Real k, Real delta_k);

/**
 * @brief Return the rotation expressed as a complex exponential associated
 * with phase accumulation of respectively the F̃_k and F̃^*_{-k} states.
 */
SYCOMORE_API std::pair<Complex, Complex> phase_accumulation(Real angle);

/**
 * @brief Return the phase accumulation expressed as a complex exponential 
 * associated with bulk motion of respectively the F̃_k, F̃^*_{-k}, and Z̃_k 
 * states.
 *
 * @param v: projection of the velocity vector on the axis associated with k.
 */
SYCOMORE_API std::tuple<Complex, Complex, Complex>
bulk_motion(Real v, Real duration, Real k, Real delta_k);

}
    
}

}

#endif // _faa6a046_30f6_4e87_91a6_033e2330b405
