#pragma once

#include <string>

struct SDL_Texture;

namespace frontier {

/// Handle for a texture
class TextureRef {
public:
    /// Get the uniuque id for the texture
    uint64_t id() const { return _id; }
    /// Get the file path
    const std::string& name() const { return _name; }
    /// Get the underlying texture (not owned)
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

} // namespace frontier
