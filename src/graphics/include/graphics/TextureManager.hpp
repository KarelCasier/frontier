#pragma once

#include <unordered_map>
#include <string>

#include <SDL2/SDL.h>

namespace frontier {

class TextureRef {
public:
    uint64_t id() { return _id; }
    const std::string& name() { return _name; }
    SDL_Texture* texture() { return _texture; }

private:
    TextureRef(uint64_t id, const std::string& name, SDL_Texture* texture)
    : _id{id}
    , _name{name}
    , _texture{texture}
    {
    }

    uint64_t _id;
    std::string _name;
    SDL_Texture* _texture;
    friend class TextureManager;
};

class TextureManager {
public:
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    TextureRef* loadTexture(const std::string& name);
    void purgeTextures();

    /// Render a texture.
    /// @param texture The texture reference obtained from a loadTexture call.
    /// @param srcRect The source rectangle of the texture.
    /// @param destRect The destination rectangle to draw the texture at.
    /// @param rotation The rotation (in radians) to draw the texture at.
    /// @param origin The point at which to rotate the srcRect at.
    void render(const TextureRef* texture, const SDL_Rect& srcRect, const SDL_Rect& destRect, const double rotation = 0.0, const SDL_Point* origin = NULL);

    SDL_Renderer* getRenderer();
private:
    std::unordered_map<uint64_t, TextureRef*> _textures;
    SDL_Renderer* _renderer;
};

} // namespace frontier
