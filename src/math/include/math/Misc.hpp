#pragma once

#include <cmath>

namespace frontier {

inline double constexpr toDegrees(const double& radians)
{
    return radians * 180.0 / M_PI;
}

inline double constexpr toRadians(const double& degrees)
{
    return degrees * M_PI / 180;
}

} // namespace frontier
