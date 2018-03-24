#pragma once

#include <unordered_map>
#include <string>

#include <graphics/TextureRef.hpp>

namespace frontier {

class Window;

/// Class to manage texture loading
class TextureManager {
public:
    /// Create a TextureManager
    /// @param window The window used to create textures
    TextureManager(std::shared_ptr<Window> window);
    ~TextureManager();

    /// Load a texture from file
    /// @param name The name of the file to load
    /// @return A pointer to the loaded texture
    TextureRef* loadTexture(const std::string& name);

    /// Purge all textures
    void purgeTextures();

private:
    class SDL_Image;

    std::unordered_map<uint64_t, TextureRef*> _textures;
    std::shared_ptr<Window> _window;
    std::unique_ptr<SDL_Image> _sdlImage;
};

} // namespace frontier
