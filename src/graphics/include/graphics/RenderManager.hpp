#pragma once

#include <SDL2/SDL_rect.h>
#include <graphics/Camera.hpp>

struct SDL_Renderer;

namespace frontier {

class ISelfRenderable;
class TextureManager;
class TextureRef;

/// Class to manager rendering
class RenderManager {
public:
    /// Create a RenderManager
    /// @param renderer The renderer to use
    /// Note: renderer is not owned by RenderManager
    RenderManager(SDL_Renderer* renderer);

    /// Render a texture.
    /// @param texture The texture reference obtained from a loadTexture call.
    /// @param srcRect The source rectangle of the texture.
    /// @param destRect The destination rectangle to render the texture at.
    /// @param rotation The rotation (in radians) to render the texture at.
    /// @param origin The point at which to rotate the srcRect at.
    void render(const TextureRef* texture,
                const SDL_Rect& srcRect,
                const SDL_Rect& destRect,
                const double rotation = 0.0,
                const SDL_Point* origin = NULL);

    /// Render a texture.
    /// @param camera The camera to use to render
    /// @param texture The texture reference obtained from a loadTexture call.
    /// @param srcRect The source rectangle of the texture.
    /// @param destRect The destination rectangle to render the texture at.
    /// @param rotation The rotation (in radians) to render the texture at.
    /// @param origin The point at which to rotate the srcRect at.
    void render(const Camera& camera,
                const TextureRef* texture,
                const SDL_Rect& srcRect,
                const SDL_Rect& destRect,
                const double rotation = 0.0,
                const SDL_Point* origin = NULL);

    /// Render a self renderable object
    /// @param renderable The object to render
    void render(ISelfRenderable* renderable);

private:
    SDL_Renderer* _renderer;
};

} // namespace frontier
