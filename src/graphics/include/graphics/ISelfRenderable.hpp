#pragma once

#include <SDL2/SDL.h>

namespace frontier {

/// Interface to allow an object to render itself to the renderer
/// Note: Used for debug rendering outside of regular systems
class ISelfRenderable {
public:
    virtual ~ISelfRenderable() = default;

    /// Render a frame to the renderer.
    /// @param renderer The renderer to use to render the frame to.
    virtual void renderSelf(SDL_Renderer* renderer) const = 0;
};

} // namespace frontier
