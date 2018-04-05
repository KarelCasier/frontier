#pragma once

#include <math/Vector2.hpp>
#include <navigation/NavPoly.hpp>

namespace frontier {

class INavAlgorithm {
public:
    virtual ~INavAlgorithm() = default;

    /// Find a path from @p initial to @p final in the @p mesh.
    /// @param mesh The mesh to seach for the path in.
    /// @param initial The initial nav poly.
    /// @param target The target nav poly.
    virtual std::vector<const NavPoly*> findNavPolyPath(const NavPoly* initial, const NavPoly* target) = 0;
};

} // namespace frontier
