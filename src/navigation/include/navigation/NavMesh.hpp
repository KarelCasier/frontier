#pragma once

#include <graphics/IRenderable.hpp>
#include <navigation/INavAlgorithm.hpp>
#include <navigation/INav.hpp>
#include <utils/Optional.hpp>

#include <vector>
#include <memory>
#include <mutex>

#include "NavPoly.hpp"

namespace frontier {

class NavMesh : public INav, public IRenderable {
public:
    NavMesh(std::unique_ptr<INavAlgorithm> navAlgorithm);

    /// Add a polygon to the mesh.
    /// @param shape The shape to add the mesh.
    void addPoly(ConvexShape<float> shape);

    /// @name INav overrides
    /// @{
    std::vector<Vector2f> findPath(const Vector2f& initial, const Vector2f& target) override;
    /// @}

    /// @name IRenderable overrides
    /// @{
    void render(IRenderTarget& renderTarget) override;
    /// @}

private:
    using StateLock = std::lock_guard<std::mutex>;

    void regenerate(const StateLock&);
    std::optional<const NavPoly*> findNavPolyContaining(const StateLock&, const Vector2f& point);

    std::unique_ptr<INavAlgorithm> _navAlgorithm;
    std::vector<NavPoly> _mesh;
    std::mutex _stateMutex;
};

} // namespace frontier
