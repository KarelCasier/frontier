#pragma once

#include <graphics/IRenderTarget.hpp>

namespace frontier {

/// Interface to allow an object to render itself to a window
class IRenderable {
public:
    virtual ~IRenderable() = default;

    /// Render a frame to the renderer.
    /// @param renderTarget The render target to render to.
    virtual void render(IRenderTarget& renderTarget) = 0;
};

} // namespace frontier
