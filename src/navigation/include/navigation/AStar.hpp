#pragma once

#include <navigation/INavAlgorithm.hpp>

namespace frontier {

class AStar : public INavAlgorithm {
public:
    /// @name INavAlgorithm overrides
    /// @{
    std::vector<const NavPoly*> findNavPolyPath(const NavPoly* initial, const NavPoly* target) override;
    /// @}
};

} // namespace frontier
