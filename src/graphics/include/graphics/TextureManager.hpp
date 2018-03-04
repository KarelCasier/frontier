#pragma once

#include <unordered_map>
#include <string>

struct SDL_Texture;
struct SDL_Renderer;

namespace frontier {

/// Handle for a texture
class TextureRef {
public:
    uint64_t id() const { return _id; }
    const std::string& name() const { return _name; }
    SDL_Texture* texture() const { return _texture; }

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

/// Class to manage texture loading
class TextureManager {
public:
    /// Create a TextureManager
    /// @param renderer The renderer used to create textures
    /// Note: renderer is not owned by TextureManager
    TextureManager(SDL_Renderer* renderer);
    ~TextureManager();

    /// Load a texture from file
    /// @param name The name of the file to load
    /// @return A pointer to the loaded texture
    TextureRef* loadTexture(const std::string& name);

    /// Purge all textures
    void purgeTextures();

private:
    std::unordered_map<uint64_t, TextureRef*> _textures;
    SDL_Renderer* _renderer;
};

} // namespace frontier
