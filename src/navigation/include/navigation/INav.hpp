#pragma once

#include <math/Vector2.hpp>

namespace frontier {

class INav {
public:
    virtual ~INav() = default;

    /// Find a path from @p initial to @p final.
    /// @param initial The initial position.
    /// @param target The target position.
    virtual std::vector<Vector2f> findPath(const Vector2f& initial, const Vector2f& target) = 0;
};

} // namespace frontier
