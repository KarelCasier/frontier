#pragma once

#include <SDL2/SDL.h>

namespace frontier {

class IDebugDrawable {
public:
    virtual ~IDebugDrawable() = default;

    /// Draw a debug frame to the renderer.
    ///
    /// @param renderer The renderer to use to draw the frame to.
    virtual void debugDraw(SDL_Renderer* renderer) const = 0;
};

} // namespace frontier
