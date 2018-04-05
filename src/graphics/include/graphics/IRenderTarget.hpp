#pragma once

#include <SDL2/SDL.h>

#include <vector>

#include <graphics/Camera.hpp>
#include <graphics/Color.hpp>
#include <graphics/PrimativeType.hpp>
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

    /// Render a vetor of vertices as @p type.
    /// @param vertices The vertices to render.
    /// @param type The primative type to render the vertices as.
    /// @param color The color to render the primative.
    virtual void render(const std::vector<Vector2f>& vertices, PrimativeType type, const Color& color) = 0;

    /// Render a vetor of vertices as @p type.
    /// @param camera The camera to use to render.
    /// @param vertices The vertices to render.
    /// @param type The primative type to render the vertices as.
    /// @param color The color to render the primative.
    virtual void render(const Camera& camera,
                        const std::vector<Vector2f>& vertices,
                        PrimativeType type,
                        const Color& color) = 0;

    /// Render a renderable object.
    /// @param renderable The object to render.
    virtual void render(IRenderable& renderable) = 0;

    /// Map a screen point to a camera point.
    /// @note Assumes current camera.
    /// @param screenPoint The point on the screen to convert.
    /// @returns The transformed point.
    virtual Vector2f screenToCamera(const Vector2i& screenPoint) const = 0;

    /// Map a camera point to a screen point.
    /// @note Assumes current camera.
    /// @param cameraPoint The point on the screen to convert.
    /// @param camera The camera to convert the point from.
    /// @returns The transformed point.
    virtual Vector2i cameraToScreen(const Vector2f& cameraPoint) const = 0;

    /// Map a screen point to a camera point.
    /// @param screenPoint The point on the screen to convert.
    /// @param camera The camera to convert the point to.
    /// @returns The transformed point.
    virtual Vector2f screenToCamera(const Vector2i& screenPoint, const Camera& camera) const = 0;

    /// Map a camera point to a screen point.
    /// @param cameraPoint The point on the screen to convert.
    /// @param camera The camera to convert the point from.
    /// @returns The transformed point.
    virtual Vector2i cameraToScreen(const Vector2f& cameraPoint, const Camera& camera) const = 0;

    /// Set the current render camera.
    /// @param camera The camera to default render to.
    virtual void setCamera(const Camera& camera) = 0;

    /// Get the current render camera.
    /// @returns The current render camea.
    virtual const Camera& getCamera() const = 0;
};

} // namespace frontier
