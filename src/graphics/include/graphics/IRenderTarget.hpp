#pragma once

#include <SDL2/SDL.h>

#include <graphics/Camera.hpp>
#include <graphics/TextureRef.hpp>
#include <math/Vector2.hpp>
#include <math/Rect.hpp>
#include <utils/Optional.hpp>

namespace frontier {

class IRenderable;

class IRenderTarget {
public:
    virtual ~IRenderTarget() = default;

    /// Called to perform pre render tasks.
    virtual void preRender() = 0;

    /// Called to perform post render tasks.
    virtual void postRender() = 0;

    /// Render a texture.
    /// @param texture The texture reference obtained from a loadTexture call.
    /// @param srcRect The source rectangle of the texture.
    /// @param destRect The destination rectangle to render the texture at.
    /// @param rotation The rotation (in radians) to render the texture at.
    /// @param origin The point at which to rotate the srcRect at. Default [dstRect.w()/2, dstRect.h()/2]
    virtual void render(const TextureRef* texture,
                const Recti& srcRect,
                const Recti& destRect,
                const double rotation = 0.0,
                const std::optional<Vector2i> origin = {}) = 0;

    /// Render a texture.
    /// @param camera The camera to use to render
    /// @param texture The texture reference obtained from a loadTexture call.
    /// @param srcRect The source rectangle of the texture.
    /// @param destRect The destination rectangle to render the texture at.
    /// @param rotation The rotation (in radians) to render the texture at.
    /// @param origin The point at which to rotate the srcRect at. Default [dstRect.w()/2, dstRect.h()/2]
    virtual void render(const Camera& camera,
                const TextureRef* texture,
                const Recti& srcRect,
                const Recti& destRect,
                const double rotation = 0.0,
                const std::optional<Vector2i> origin = {}) = 0;

    /// Render a renderable object
    /// @param renderable The object to render
    virtual void render(IRenderable& renderable) = 0;
};

} // namespace frontier
